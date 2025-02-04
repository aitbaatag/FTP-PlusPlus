#ifndef SERVER_HPP
#define SERVER_HPP
#include "../Socket/Socket.hpp"
#include "../Server/Cmdhandler.hpp"
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <algorithm>
#include <vector>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

class Server : public Socket {
private:
  std::vector<int> client_fds;
  int client_fd;
  Cmdhandler cmdhandler;
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
  void HandleClientMessage(int client_fd);
  int get_port() const;
};

void PrintServerIP(int port);

#endif // SERVER_HPP
