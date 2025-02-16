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
int DataConnection::recv_data_port(int client_fd) {
  char buffer[1024] = {0};
  int bytes_read = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
  if (bytes_read <= 0) {
    std::cerr << "Failed to receive data port from server\n";
    return -1;
  }

  // Parse the data port from the server's message
  std::string port_message(buffer);
  size_t start = port_message.find('(');
  size_t end = port_message.find(')');
  if (start == std::string::npos || end == std::string::npos) {
    std::cerr << "Invalid data port message from server\n";
    return -1;
  }

  std::string port_str = port_message.substr(start + 1, end - start - 1);
  std::vector<std::string> parts;
  size_t pos = 0;
  while ((pos = port_str.find(',')) != std::string::npos) {
    parts.push_back(port_str.substr(0, pos));
    port_str.erase(0, pos + 1);
  }
  parts.push_back(port_str); // Add the last part

  if (parts.size() != 6) {
    std::cerr << "Invalid data port format from server\n";
    return -1;
  }

  // Extract p1 and p2
  int p1 = std::stoi(parts[4]);
  int p2 = std::stoi(parts[5]);
  int data_port = p1 * 256 + p2;

  return data_port;
}
void DataConnection::ConnectToServer(int data_port) {
  // server_addr.sin_port = htons(data_port);
  if (connect(sockfd, (sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
    std::cerr << "Failed to connect to the server (data connection)\n";
    exit(1);
  }
}
int DataConnection::CreateDataConnection(int client_fd,
                                         const std::string &server_ip) {
  CreateTCPIpv4Socket();
  if (server_ip.empty()) { // For server
    InitSocketAdd();
    BindSocket();
    sockaddr_in assigned_addr{};
    socklen_t addr_len = sizeof(assigned_addr);
    getsockname(sockfd, (sockaddr *)&assigned_addr, &addr_len);
    int data_port = ntohs(assigned_addr.sin_port);

    ListenSocket();
    // Send port to client
    SendDataPort(data_port, client_fd);
  } else { // For client
    int data_port = recv_data_port(client_fd);
    if (data_port < 0) {
      exit(1);
    }
    char *c_server_ip = const_cast<char *>(server_ip.c_str());
    set_port(data_port);
    InitSocketAdd(c_server_ip);
    ConnectToServer(data_port);
    return sockfd; // data socket
  }
  return AcceptDataConnection(client_fd);
}
// sockfd ""==> data socket
int DataConnection::AcceptDataConnection(int client_fd) {

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
