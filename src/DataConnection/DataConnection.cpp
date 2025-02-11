#include "DataConnection.hpp"

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
    server_addr.sin_port = htons(data_port);
    if (connect(sockfd, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "Failed to connect to the server (data connection)\n";
        exit(1);
    }
}

int DataConnection::CreateDataConnection(int client_fd, const std::string& server_ip) {
    CreateTCPIpv4Socket();
    if (server_ip.empty()) { // For server
        InitSocketAdd();
        BindSocket();
        ListenSocket();
    } else { // For client
        char* c_server_ip = const_cast<char*>(server_ip.c_str());
        InitSocketAdd(c_server_ip);
    }
    return AcceptDataConnection(client_fd);
}

int DataConnection::AcceptDataConnection(int client_fd) {
    sockaddr_in assigned_addr{};
    socklen_t addr_len = sizeof(assigned_addr);
    getsockname(sockfd, (sockaddr*)&assigned_addr, &addr_len);
    int data_port = ntohs(assigned_addr.sin_port);

    // Send port to client
    SendDataPort(data_port, client_fd);

    sockaddr_in client_data_add{};
    socklen_t client_data_len = sizeof(client_data_add);
    int client_data_sockfd = accept(sockfd, (sockaddr*)&client_data_add, &client_data_len);
    if (client_data_sockfd < 0) {
        perror("Data accept failed");
        close(sockfd);
        return -1;
    }

    close(sockfd);
    return client_data_sockfd;
}