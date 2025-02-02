#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

class Socket {
protected:
    int sockfd;
    int port;
    struct sockaddr_in server_addr;
    socklen_t addrlen;

public:
    Socket(int port);
    virtual ~Socket();
    void CreateTCPIpv4Socket();
    void InitSocketAdd(); // for server
    void InitSocketAdd(char *server_ip); // for client
    void BindSocket();
    void ListenSocket();
    virtual void AcceptConnection();
    int Get_sockfd();
};

#endif // SOCKET_HPP

