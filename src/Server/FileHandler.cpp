#include "../../inc/Server/FileHandler.hpp"

FileHandler::FileHandler() { current_dir = fs::current_path(); }
void FileHandler::ChangeDirectory(int client_fd, const std::string &new_dir) {
  fs::path new_path = current_dir / new_dir;
  if (fs::exists(new_path) && fs::is_directory(new_path)) {
    current_dir = new_path;
    std::cout << current_dir << std::endl;
    SendResponse(client_fd,
                 "Directory changed to " + current_dir.string() + "\r\n");
  } else {
    SendResponse(client_fd, "Failed to change directory\r\n");
  }
}
void FileHandler::SendResponse(int client_fd, const std::string &response) {
  send(client_fd, response.c_str(), response.size(), 0);
}
void FileHandler::ListFiles(int client_fd) {
  std::string file_list = "Here comes the directory listing\r\n";
  std::cout << current_dir << std::endl;
  for (const auto &entry : fs::directory_iterator(current_dir)) {
    std::string entry_name = entry.path().filename().string();

    if (fs::is_directory(entry)) {
      // Directories in blue
      file_list += "\033[34m" + entry_name + "\033[0m\r\n";
    } else if (fs::is_regular_file(entry)) {
      // Regular files in green
      file_list += "\033[32m" + entry_name + "\033[0m\r\n";
    } else {
      // Other types (e.g., symlinks) in default color
      file_list += entry_name + "\r\n";
    }
  }

  file_list += "Directory send OK\r\n";
  SendResponse(client_fd, file_list);
}
bool FileHandler::OpenFile(std::fstream &file, fs::path filepath,
                           std::ios_base::openmode mode, int client_fd) {
  file.open(filepath, mode);
  if (!file.is_open()) {
    SendResponse(client_fd, "Failed to open file\r\n");
    return false;
  }
  return true;
}

bool FileHandler::fileExists(const std::string &filepath) {
  return std::filesystem::exists(filepath);
}

bool FileHandler::uPLOAD(int client_fd, const std::string &fileName) {
  ServerDataConnection serverdataconnection;
  int data_socket = serverdataconnection.CreateServerDataConnection(client_fd);
  if (data_socket < 0) {
    SendResponse(client_fd, "425 Can't open data connection\r\n");
    return false;
  }
  fs::path file_path = current_dir / fileName;
  std::fstream file;
  if (!OpenFile(file, file_path, std::ios::binary | std::ios::out, client_fd)) {
    SendResponse(client_fd, "Server Failed to create file\r\n");
    std::cerr << "Failed to create file\n";
    return false;
  }

  char buffer[BUFF_SIZE];
  size_t totalBytes = 0;

  while (true) {
    int valread = recv(data_socket, buffer, BUFF_SIZE, 0);
    if (valread < 0) {
      send(client_fd, "ERROR: File transfer failed\n", 27, 0);
      file.close();
      return false;
    } else if (valread == 0) {
      break; // End of file
    }
    file.write(buffer, valread);
    totalBytes += valread;
  }

  file.close();
  send(client_fd, "226 Transfer complete\r\n", 23, 0);
  return true;
}
bool FileHandler::dOWNLOAD(int client_fd, const std::string &fileName) {
  fs::path file_path = current_dir / fileName;

  // Check if the file exists
  if (!fs::exists(file_path)) {
    SendResponse(client_fd, "550 File not found\r\n");
    return false;
  }

  // Create a data connection
  ServerDataConnection serverDataConnection;
  int data_socket = serverDataConnection.CreateServerDataConnection(client_fd);
  if (data_socket < 0) {
    SendResponse(client_fd, "425 Can't open data connection\r\n");
    return false;
  }

  // Open the file
  std::ifstream file(file_path, std::ios::binary);
  if (!file.is_open()) {
    SendResponse(client_fd, "550 Failed to open file\r\n");
    close(data_socket);
    return false;
  }

  // Send the file over the data connection
  char buffer[BUFF_SIZE];
  while (file.read(buffer, sizeof(buffer))) {
    if (send(data_socket, buffer, file.gcount(), 0) < 0) {
      perror("Send failed");
      file.close();
      close(data_socket);
      return false;
    }
  }

  // Send any remaining data
  if (file.gcount() > 0) {
    if (send(data_socket, buffer, file.gcount(), 0) < 0) {
      perror("Send failed");
      file.close();
      close(data_socket);
      return false;
    }
  }

  file.close();
  close(data_socket);

  // Notify the client that the transfer is complete
  SendResponse(client_fd, "226 Transfer complete\r\n");
  return true;
}
fs::path FileHandler::GetCurrent_dir() const { return (current_dir); }
