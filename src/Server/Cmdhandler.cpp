#include "../../inc/Server/Cmdhandler.hpp"

Cmdhandler::Cmdhandler(int client_fd) : buffer({0})
{
  this->client_fd = client_fd;
}
void Cmdhandler::GetCmd()
{
  int valread;
  std::string input;

  valread = recv(client_fd, buffer, BUFF_SIZE, 0);
  if (valread < 0)
  {
    perror("Recv failed");
    exit(EXIT_FAILURE);
  }
  std::istringstream iss(input);
  iss >> cmd;
  iss >> fileName;
}
void Cmdhandler::ProcessCmd()
{
  if (cmd == UPLOAD) {
      std::cout << "Uploading file: " << fileName << "\n";
  }
  else if (cmd == DOWNLOAD) {
    std::cout << "Downloading file: " << fileName << "\n";
  }
  else if (cmd == EXIT) {
    std::cout << "Client requested to exit\n";
  }
  else {
    std::cout << "Invalid command. Available commands: 'upload <filename>', 'download <filename>', 'exit'\n";
  }
}
