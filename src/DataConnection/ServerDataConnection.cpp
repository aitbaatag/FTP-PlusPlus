#include "../../inc/DataConnection/ServerDataConnection.hpp"

ServerDataConnection::ServerDataConnection() : DataConnection() {}

ServerDataConnection::~ServerDataConnection() {}

int ServerDataConnection::CreateServerDataConnection(int client_fd) {
  return CreateDataConnection(client_fd, ""); // No server_ip for server
}
