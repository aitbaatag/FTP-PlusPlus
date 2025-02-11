#include "ClientDataConnection.hpp"

ClientDataConnection::ClientDataConnection(const std::string& server_ip)
    : DataConnection(), server_ip(server_ip) {}

ClientDataConnection::~ClientDataConnection() {}

int ClientDataConnection::CreateClientDataConnection(int client_fd) {
    return CreateDataConnection(client_fd, server_ip);
}