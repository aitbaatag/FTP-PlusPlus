#ifndef DATACONNECTION_HPP
#define DATACONNECTION_HPP

#include "../Socket/Socket.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <string>
#include <vector>
class DataConnection : public Socket {
public:
  DataConnection();
  virtual ~DataConnection();

  void SendDataPort(int data_port, int client_fd);
  void ConnectToServer();

protected:
  int CreateDataConnection(int client_fd, const std::string &server_ip = "");
  int AcceptDataConnection();
  int get_data_socket() const;

private:
  int recv_data_port(int clinet_fd);
};

#endif
