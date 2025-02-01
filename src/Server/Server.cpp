#include "../../inc/Server/Server.hpp"

Server::Server(int port) :  Socket(port) 
{
  FD_ZERO(&master_fds);
  FD_ZERO(&ready_fds);
}

Server::~Server()
{
    Server::~Socket();
}
std::string Server::get_client_ip(const sockaddr_in& client_addr) {
    char ip_str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &client_addr.sin_addr, ip_str, INET_ADDRSTRLEN);
    return std::string(ip_str);
}
Server::AcceptConnection()
{
  addrlen = sizeof();
  client_fd = accept(sockfd, (struct sockaddr*)&client_addr, &addrlen);
  if (client_fd == -1) {
    std::cerr << "Failed to accept connection\n";
    exit(1);
  }
}
void Server::HandleNewConnection()
{
  std::string clinet_ip;
  AcceptConnection();
  client_fds.push_back(client_fd);
  FD_SET(client_fd, &master_fds);
  max_fd = std::max(max_fd, client_fd);
  client_ip = get_client_ip(client_addr);
  std::cout << "New connection from " << client_ip << " on socket " << client_fd << std::endl;
}

void Server::StartServer()
{
    CreateSocket();
    InitSocketAdd(); // TODO
    BindSocket();
    ListenSocket();
    FD_SET(sockfd, &master_fds); // Add server socket to master set
    max_fd = sockfd;

    while (true)
    {
      ready_fds = master_fds;
      if (select(max_fd + 1, ready_fds, NULL, NULL, NULL) < 0)
      {
        std::perror("select error\n");
        exit(1)
      }
      for (int fd, fd <= max_fd, fd++)
      {
        if (FD_ISSET(fd, &ready_fds)) {
          if (fd == sockfd) {
            // this is a new Connection
            HandleNewConnection();
          }
        }
      }
    }
}a
