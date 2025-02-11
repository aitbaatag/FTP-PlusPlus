#ifndef SERVERDATACONNECTION_HPP
#define SERVERDATACONNECTION_HPP

#include "DataConnection.hpp"

class ServerDataConnection : public DataConnection {
public:
    ServerDataConnection();
    ~ServerDataConnection();

    int CreateServerDataConnection(int client_fd);
};

#endif