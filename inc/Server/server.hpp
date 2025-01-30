#ifndef SERVER_HPP
#define SERVER_HPP
#include "../Socket/"
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

class Server : public Socket {
public:
    Server(int port);
    ~Server();

    void StartServer();
};

#endif // SERVER_HPP
