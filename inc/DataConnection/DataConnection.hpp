#ifndef DATACONNECTION_HPP
#define DATACONNECTION_HPP

#include "../Socket/Socket.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <string>
class DataConnection : public Socket {
public:
  DataConnection();
  virtual ~DataConnection();

  void SendDataPort(int data_port, int client_fd);
  void ConnectToServer(int data_port);

protected:
  int CreateDataConnection(int client_fd, const std::string &server_ip = "");
  int AcceptDataConnection(int client_fd);
  int get_data_socket() const;
};

#endif
