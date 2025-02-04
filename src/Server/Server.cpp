#include "../../inc/Server/Server.hpp"

Server::Server(int port) :  Socket(port) 
{
  FD_ZERO(&master_fds);
  FD_ZERO(&ready_fds);
}

Server::~Server()
{

}

std::string Server::get_client_ip(const sockaddr_in& client_addr) {
    char ip_str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &client_addr.sin_addr, ip_str, INET_ADDRSTRLEN);
    return std::string(ip_str);
}
void Server::AcceptConnection()
{
  addrlen = sizeof(client_addr);
  this->client_fd = accept(sockfd, (struct sockaddr*)&client_addr, &addrlen);
  if (client_fd == -1) {
    std::cerr << "Failed to accept connection\n";
    exit(1);
  }
}
void Server::HandleNewConnection()
{
  std::string client_ip;
  AcceptConnection();
  client_fds.push_back(client_fd);
  FD_SET(client_fd, &master_fds);
  max_fd = std::max(max_fd, client_fd);
  client_ip = get_client_ip(client_addr);
  std::cout << "New connection from " << client_ip << " on socket " << client_fd << std::endl;
}

 void Server::HandleClientMessage(int client_fd) {
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));
        
        int bytes_read = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
        if (bytes_read <= 0) {
            if (bytes_read == 0) {
                std::cout << "Client on socket " << client_fd << " disconnected" << std::endl;
            } else {
                perror("recv failed");
            }
            
            // Remove client from our data structures
            //close(client_fd);
            //FD_CLR(client_fd, &master_fds);
            //client_fds.erase(std::remove(client_fds.begin(), client_fds.end(), client_fd), client_fds.end());
        } else {
            buffer[bytes_read] = '\0';
            
            // Create command handler instance and process the command
            
            // Echo back to client
            std::string rec(buffer);
            std::string response = "Server received: " + std::string(buffer);
            std::cout << "I get " + rec << std::endl;
            send(client_fd, response.c_str(), response.length(), 0);
        }
    }

void Server::StartServer()
{
    CreateTCPIpv4Socket();
    PrintServerIP(port);
    InitSocketAdd();
    BindSocket();
    ListenSocket();
    FD_SET(sockfd, &master_fds); // Add server socket to master set
    max_fd = sockfd;

    while (true)
    {
      ready_fds = master_fds;
      if (select(max_fd + 1, &ready_fds, NULL, NULL, NULL) < 0)
      {
        std::perror("select error\n");
        exit(1);
      }
      for (int fd = 0; fd <= max_fd; fd++)
      {
        if (FD_ISSET(fd, &ready_fds)) {
          if (fd == sockfd) {
            // this is a new Connection
            HandleNewConnection();
          }
          else
          {
            // TODO
            HandleClientMessage(client_fd);
            FD_CLR(fd, &master_fds);
          }
        }
      }
    }
}

int Server::get_port() const
{
  return (port);
}

void PrintServerIP(int port) {
    char hostbuffer[256];
    char ip[INET_ADDRSTRLEN];
    struct hostent *host_entry;
    
    // Get the hostname
    if (gethostname(hostbuffer, sizeof(hostbuffer)) < 0) {
        perror("gethostname");
        return;
    }
    
    // Get host information
    if ((host_entry = gethostbyname(hostbuffer)) == NULL) {
        perror("gethostbyname");
        return;
    }
    
    // Convert IP to string
    inet_ntop(AF_INET, host_entry->h_addr_list[0], ip, sizeof(ip));
    std::cout << "Server IP: " << ip << " Port: " << port << std::endl;
}

