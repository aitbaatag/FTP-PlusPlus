#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <iostream>    // For printing output to console
#include <cstring>     // For memset and string handling
#include <unistd.h>    // For close() (optional)
#include <arpa/inet.h> // For sockaddr_in and inet_addr() functions
#include <sys/socket.h> // For socket(), bind(), listen(), accept(), etc.
class Socket
{
    private:
        int sockfd;
        socklen_t addrlen;
        struct sockaddr_in server_addr;
        int client_fd;
        int port;
    public:
        Socket(int port);
        ~Socket(void);
        void CreateSocket();
        int Get_sockfd();
        void InitSocketAdd();
        void BindSocket();
        void ListenSocket();
        void AcceptConnection();
        int get_client_fd() const;
};
#endif
