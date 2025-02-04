#include "../../inc/Server/FileHandler.hpp"

FileHandler::FileHandler(int client_fd)
{
  this->client_fd = client_fd;
}

int FileHandler::OpenFile(std::string FilePath) {
  File(FilePath);
  if (File.is_open() <= 0) {
    std::cerr << "Unable to create file" << std::endl;
    return 1;
  }
  return 0;
}

bool FileHandler::UPLOADD(std::string FileName) {
  std::string filepath;
  filepath = storagePath + FileName;

  if (OpenFile(filepath, std::ios::binary)) {
    send(client_fd, "ERRO\n", 6, 0);
    return;
  }
  char buffer[BUFF_SIZE];
  size_t totalBytes = 0;

  while (true) {
    int valread = recv(client_fd, buffer, BUFF_SIZE, 0);
    buffer[valread] = '\0';
    if (valread < 0)
    {
      send(client_fd, "ERROR\n", 6);
      break ;
    }
    else if (valread ==  && buffer[0] == '\0')
    {
      break ;
    }
    File.write(buffer, valread);
    totalBytes += valread;
  }
  File.close;
  send(client_fd, "SUCCESS", 7, 0);
}

bool FileHandler::DOWNLOAD(std::string FileName) {
  std::string filepath;

  filepath = storagePath + FileName;
  if (OpenFile(filepath, std::ios::binary)) {
    send(client_fd, "ERRO\n", 6, 0);
    return;
  }
  char buffer[BUFF_SIZE];
  size_t totalBytes = 0;

  while (int valread = File.read(buffer, sizeof(buffer)) {
    send(client_fd, buffer, BUFF_SIZE, 0);
    totalBytes += valread;
  }
  File.close;
  send(client_fd, "SUCCESS", 7, 0);
}

