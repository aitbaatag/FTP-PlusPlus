#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

class Socket {
protected:
    int sockfd;
    int client_fd;
    int port;
    struct sockaddr_in server_addr;
    socklen_t addrlen;

public:
    Socket(int port);
    virtual ~Socket();

    void CreateSocket();
    void InitSocketAdd();
    void BindSocket();
    void ListenSocket();
    void AcceptConnection();
    
    int get_client_fd() const;
    int Get_sockfd();
};

#endif // SOCKET_HPP

