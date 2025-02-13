#ifndef CLIENTDATACONNECTION_HPP
#define CLIENTDATACONNECTION_HPP

#include "DataConnection.hpp"

class ClientDataConnection : public DataConnection {
public:
  ClientDataConnection(const std::string &server_ip);
  ~ClientDataConnection();

  int CreateClientDataConnection(int client_fd);

private:
  std::string server_ip;
};

#endif
