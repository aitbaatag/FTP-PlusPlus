#include "../../inc/Socket/Socket.hpp"

Socket::Socket(int port)
{
    this->port = port;
}

void Socket::CreateTCPIpv4Socket()
{
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        std::cerr << "Failed to create socket\n";
        exit(1);
    }
}

void Socket::InitSocketAdd()
{
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;
}

void Socket::InitSocketAdd(char *server_ip)
{
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  // Convert IP address from string to binary form
  if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
    std::perror("Invalid address");
    exit(EXIT_FAILURE);
  }
}

void Socket::BindSocket()
{
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "Failed to bind socket\n";
        exit(1);
    }
}

void Socket::ListenSocket()
{
    if (listen(sockfd, 5) == -1) {
        std::cerr << "Failed to listen on socket\n";
        exit(1);
    }
}

void Socket::AcceptConnection()
{
  // implemented by server class 
}

int Socket::Get_sockfd()
{
    return sockfd;
}

Socket::~Socket()
{
}
