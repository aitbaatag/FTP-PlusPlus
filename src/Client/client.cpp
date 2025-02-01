#include "../../inc/Client/Client.hpp"

Client::Client(const char *server_ip, int port) : Socket(port), server_ip(server_ip)
{

}
Client::~Client()
{
}
void Client::InitSocketAdd()
{
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  // Convert IP address from string to binary form
  if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
    std::perror("Invalid address");
    exit(EXIT_FAILURE);
  }
}
void Client::ConnectToServer()
{
    if (connect(sockfd, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "Failed to connect to the server\n";
        exit (1);
    }
    std::cout << "Successfully connected to the server\n";

}
int Client::Get_sockfd() const
{
    return sockfd;
}
