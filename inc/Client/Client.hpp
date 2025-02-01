#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../Socket/Socket.hpp"
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

class Client : public Socket {
private:
  const char *server_ip;
public:
    Client(const char *server_ip, int port);
    ~Client();

    void ConnectToServer();
    int Get_sockfd() const;
};

#endif // CLIENT_HPP

