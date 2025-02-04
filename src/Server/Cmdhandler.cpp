#include "../../inc/Server/Cmdhandler.hpp"

Cmdhandler::Cmdhandler(int client_fd) : buffer({0})
{
  this->client_fd = client_fd;
}
void Cmdhandler::GetCmd()
{
  int valread;

  valread = recv(client_fd, buffer, BUFF_SIZE, 0);
  if (valread < 0)
  {
    perror("Recv failed");
    exit(EXIT_FAILURE);
  }
  buffer[valread] = '\0';
  std::istringstream iss(buffer);
  iss >> cmd;
  iss >> fileName;
}
void Cmdhandler::ProcessCmd()
{
  FileHandler filehandler(); // TODO

  if (cmd == UPLOAD) {
    filehandler.UPLOAD(fileName);
  }
  else if (cmd == DOWNLOAD) {
    filehandler.DOWNLOAD(fileName);
  }
  else if (cmd == EXIT) {
    exit(1);
  }
  else {
    std::cout << "Invalid command. Available commands: 'upload <filename>', 'download <filename>', 'exit'\n";
  }
}
