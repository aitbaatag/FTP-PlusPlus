#include "../../inc/Server/Cmdhandler.hpp"
#include <iostream>

Cmdhandler::Cmdhandler() {}
void Cmdhandler::setFdClient(int client_fd) { this->client_fd = client_fd; }
void Cmdhandler::GetCmd() {
  int valread;

  valread = recv(client_fd, buffer, CBUFF_SIZE, 0);
  if (valread < 0) {
    perror("Recv failed");
    exit(EXIT_FAILURE);
  }
  buffer[valread] = '\0';
  std::istringstream iss(buffer);
  iss >> cmd;
  iss >> fileName;
}
void Cmdhandler::ProcessCmd() {
  FileHandler filehandler;

  if (cmd == UPLOAD) {
    filehandler.uPLOAD(client_fd, fileName);
    send(client_fd, "\n", 1, 0);
    std::cout << "uplaod\n";
  } else if (cmd == DOWNLOAD) {
    filehandler.dOWNLOAD(client_fd, fileName);
    send(client_fd, "\n", 1, 0);
    std::cout << "download\n";
  } else if (cmd == EXIT) {
    send(client_fd, "Goodbye\n", 12, 0);
  } else if (cmd == LIST) {
    filehandler.ListFiles(client_fd);
  } else if (cmd == CWD) {
    filehandler.ChangeDirectory(client_fd, fileName);
  } else if (cmd == PWD) {
    filehandler.SendResponse(
        client_fd, "\"" + filehandler.GetCurrent_dir().string() + "\"\r\n");
  } else {
    std::cout << cmd << fileName << std::endl;
    send(client_fd, "Unknown command\n", 20, 0);
  }
}
