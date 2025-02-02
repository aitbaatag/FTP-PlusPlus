#ifndef SERVER_HPP
#define SERVER_HPP
#include "../Socket/Socket.hpp"
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <algorithm>
#include <vector>

class Server : public Socket {
private:
  std::vector<int> client_fds;
  int client_fd;
  fd_set master_fds;
  fd_set ready_fds;
  int max_fd;
  struct sockaddr_in client_addr;
public:
  Server(int port);
  ~Server();
  void StartServer();
  void HandleNewConnection();
  std::string get_client_ip(const sockaddr_in& client_addr);
  void AcceptConnection();
};

#endif // SERVER_HPP
