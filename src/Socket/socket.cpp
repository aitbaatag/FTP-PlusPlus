#include "../../inc/Socket/Socket.hpp"

Socket::Socket(int port)
{
    this->port = port;
}

void Socket::CreateSocket()
{
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        std::cerr << "Failed to create socket\n";
        exit(1);
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

int Socket::AcceptConnection()
{
  // implemented by server class 
}

int Socket::get_client_fd() const
{
    return client_fd;
}

int Socket::Get_sockfd()
{
    return sockfd;
}

Socket::~Socket()
{
    close(sockfd);
}
