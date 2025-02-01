#ifndef SERVER_HPP
#define SERVER_HPP
#include "../Socket/"
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

class Server : public Socket {
private:
  std::vector<int> client_fds;
  int client_fd;
  fd_set master_fds;
  fd_set read_fds;
  int max_fd;
  struct sockaddr_in client_addr;
public:
  Server(int port);
  ~Server();
  void StartServer();
  void HandleNewConnection();
  int get_client_ip();
};

#endif // SERVER_HPP
