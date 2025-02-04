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
  // FileHandler filehandler(client_fd);

  if (cmd == UPLOAD) {
    // filehandler.UPLOAD(fileName);
    std::cout << "uplaod\n";
  }
  else if (cmd == DOWNLOAD) { 
    filehandler.DOWNLOAD(fileName);
    std::cout << "download\n";
  }
  else if (cmd == EXIT) {
    send(client_fd, "Goodbye\n", 12, 0);
  }
  else {
    send(client_fd, "Unknown command\n", 20, 0);
  }
}
