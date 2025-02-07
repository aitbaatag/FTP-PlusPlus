#include "../../inc/DataConnection/DataConnection.hpp"

DataConnection::DataConnection() : Socket(0) {}
int DataConnection::CreateDataConnection(int client_fd, std::string server_ip) {
  CreateTCPIpv4Socket();
  if (server_ip.empty()) // for server class
  {
    InitSocketAdd();
    BindSocket();
    ListenSocket();
  } else {
    InitSocketAdd(server_ip); // for client class
  }
  // Accept data connection
  return (AcceptDataConnectin());
}
int DataConnection::AcceptDataConnection() {
  // TODO send data port to client
  sockaddr_in client_data_add{};
  socklen_t client_data_len = sizeof(client_data_add);
  int client_data_sockfd =
      accept(fdsock, (sockaddr *)&client_data_add, &client_data_len);
  if (client_data_sockfd < 0) {
    perror("Data accept failed");
    close(data_sockfd);
    return -1;
  }
  close(data_sockfd);
  return client_data_sockfd;
}
