#include "../../inc/Client/Client.hpp"
#include <iostream>

Client::Client(const std::string &server_ip, int port)
    : Socket(port), server_ip(server_ip) {}

Client::~Client() {}
bool Client::SendMessage(const std::string &message) {
  if (send(sockfd, message.c_str(), message.length(), 0) < 0) {
    perror("Send failed");
    return false;
  }
  return true;
}
std::string Client::ReceiveMessage() {
  char buffer[1024] = {0};
  int bytes_read = recv(sockfd, buffer, 1024, 0);
  if (bytes_read < 0) {
    perror("Receive failed");
    return "";
  }
  buffer[bytes_read] = '\0';
  return std::string(buffer);
}
Client::Cinput Client::SplitInput(const std::string &input) {
  Cinput cinput;
  std::istringstream iss(input);
  iss >> cinput.cmd;
  iss >> cinput.filename;
  return cinput;
}
void Client::ConnectToServer() {
  FileManager filemanager(sockfd, server_ip);
  std::string input;
  if (connect(sockfd, (sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
    std::cerr << "Failed to connect to the server\n";
    exit(1);
  }
  std::cout << "Successfully connected to the server\n";

  while (true) {
    std::getline(std::cin, input);
    Cinput cinput = SplitInput(input);
    if ((cinput.cmd == "LIST" || cinput.cmd == "PWD" || cinput.cmd == "CWD" ||
         cinput.cmd == "exit") &&
        cinput.filename.empty()) {
      SendMessage(cinput.cmd);
      if (cinput.cmd == "exit") {
        std::cout << ReceiveMessage();
        close(sockfd);
        exit(1);
      }
    } else if (cinput.cmd == "download") {
      filemanager.download(cinput.filename);
    } else if (cinput.cmd == "upload") {
      filemanager.upload(cinput.filename);
    } else {
      std::cout << "Invalid command. Use 'upload <filename>' or 'download "
                   "<filename>'.\n";
    }
    std::cout << ReceiveMessage();
  }
}
int Client::Get_sockfd() const { return sockfd; }
