#include "../../inc/DataConnection/DataConnection.hpp"
#include <cstddef>
#include <iostream>
#include <iterator>
#include <string>

DataConnection::DataConnection() : Socket(0) {}

DataConnection::~DataConnection() {}

void DataConnection::SendDataPort(int data_port, int client_fd) {
  std::string port_message = "227 Entering Passive Mode (127,0,0,1," +
                             std::to_string(data_port / 256) + "," +
                             std::to_string(data_port % 256) + ")\r\n";
  if (send(client_fd, port_message.c_str(), port_message.length(), 0) < 0) {
    std::cerr << "Failed to send port to client\n";
    exit(1);
  }
}

void DataConnection::ConnectToServer(int data_port) {
  // server_addr.sin_port = htons(data_port);
  if (connect(sockfd, (sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
    std::cerr << "Failed to connect to the server (data connection)\n";
    exit(1);
  }
}
int DataConnection::recv_data_port(int client_fd) {
  char buff[1024] = {0};
  int bytes_read = recv(client_fd, buff, sizeof(buff), 0);
  if (bytes_read < 0) {
    std::cerr << "receive failed\n";
    exit(1);
  }
  buff[bytes_read] = '\0';
  std::string port_message(buff);
  // parse data port
  size_t start = port_message.find('(');
  size_t end = port_message.find(')');
  std::string port_str = port_message.substr(start + 1, end + 1);
  int p1 = std::stoi(port_str.substr(0, port_str.find(',')));
  int p2 = std::stoi(port_str.substr(port_str.find(',') + 1));
  int data_port = p1 * 256 + p2;
  return (data_port);
}
int DataConnection::CreateDataConnection(int client_fd,
                                         const std::string &server_ip) {
  CreateTCPIpv4Socket();
  if (server_ip.empty()) { // For server
    InitSocketAdd();
    BindSocket();
    ListenSocket();
  } else { // For client
    int data_port = recv_data_port(client_fd);
    char *c_server_ip = const_cast<char *>(server_ip.c_str());
    set_port(data_port);
    InitSocketAdd(c_server_ip);
    ConnectToServer(data_port);
    return sockfd; // data socket
  }
  return AcceptDataConnection(client_fd); // data socket for server
}
// sockfd ==> data socket
int DataConnection::AcceptDataConnection(int client_fd) {
  sockaddr_in assigned_addr{};
  socklen_t addr_len = sizeof(assigned_addr);
  getsockname(sockfd, (sockaddr *)&assigned_addr, &addr_len);
  int data_port = ntohs(assigned_addr.sin_port);

  // Send port to client
  SendDataPort(data_port, client_fd);

  sockaddr_in client_data_add{};
  socklen_t client_data_len = sizeof(client_data_add);
  int client_data_sockfd =
      accept(sockfd, (sockaddr *)&client_data_add, &client_data_len);
  if (client_data_sockfd < 0) {
    perror("Data accept failed");
    close(sockfd);
    return -1;
  }

  close(sockfd);
  return client_data_sockfd;
}
