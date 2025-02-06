#include "../../inc/Client/FileManager.hpp"

FileManager::FileManager(int fdsocket) {
  this->fdsocket = fdsocket;
}
bool FileManager::OpenFile(std::fstream& file, fs::path filepath, std::ios_base::openmode mode) {
    file.open(filepath, mode);
    if (!file.is_open()) {
      std::cout << "Failed to open file\r\n";
        return false;
    }
    return true;
}

bool FileManager::fileExists(const std::string& filepath) {
    return std::filesystem::exists(filepath);
}
void FileManager::download(const std::string& fileName) {
  std::fstream file;
  if (!OpenFile(file, file_path, std::ios::binary | std::ios::out, client_fd)) {
    std::cerr << "Failed to create file\n";
    return ;
  }

    char buffer[BUFF_SIZE];
    size_t totalBytes = 0;

    while (true) {
        int valread = recv(fdsocket, buffer, BUFF_SIZE, 0);
        if (valread < 0) {
          std::cerr << "ERROR: File transfer failed\n";
            file.close();
            return ;
        } else if (valread == 0) {
            break ; // End of file
        }
        file.write(buffer, valread);
        totalBytes += valread;
    }

    file.close();
    std::cout << "SUCCESS: File downloaded\n";
}
void FileHandler::upload(const std::string& fileName) {
  if (!fs::exists(file_path)) {
    std::cerr << "File not found\r\n";
    return ;
  }
  std::fstream file;
  if (!OpenFile(file, file_path, std::ios::binary | std::ios::in, client_fd)) {
    std::cerr << "ERROR: Unable to open file\n";
    return ;
  }
  char buffer[BUFF_SIZE];
  size_t totalBytes = 0;
  while (!file.eof()) {
    file.read(buffer, sizeof(buffer));
    int valread = file.gcount();
    if (valread > 0) {
      if (send(client_fd, buffer, valread, 0) < 0) {
        file.close();
        return ;
      }
      totalBytes += valread;
    }
  }
  file.close();
  std::cout << "SUCCESS: File uploaded\n";
  return ;
}

