#include "../../inc/Client/Client.hpp"

Client::Client(const char *server_ip, int port) : Socket(port), server_ip(server_ip)
{
  (void)server_ip;
}

Client::~Client()
{
}
bool Client::SendMessage(const std::string& message) {
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
Cinput &SplitInput(const std::string &input)
{
  Cinput cinput;
  std::istringstream iss(input);
  iss >> cinput.cmd;
  iss >> cinout.filename;
  return cinput;
}
void Client::ConnectToServer()
{
  FileManager filemanager(sockfd);
  std::striinputt;
    if (connect(sockfd, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "Failed to connect to the server\n";
        exit (1);
    }
    std::cout << "Successfully connected to the server\n";

    while (true)
    {
      std::getline(std::cin, input);
      if (SplitInput(input).cmd.equle("upload"))
      {
        FileManager.download(SplitInput(input).filename;
      }
      else if (SplitInput(input).cmd.equle("download"))
      {
        FileManager.upload(SplitInput(input).filename);
      }
      std::cout << ReceiveMessage();
    }
}
int Client::Get_sockfd() const
{
    return sockfd;
}
