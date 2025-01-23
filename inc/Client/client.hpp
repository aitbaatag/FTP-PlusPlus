#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../../inc/Socket/Socket.hpp"
class Client
{
    private:
        int sockfd;
        int port;
        struct sockaddr_in server_addr;
    public:
        Client(int port);
        ~Client();
        void CreateSocket();
        void InitSocketAdd();
        void ConnectToServer();
        int Get_sockfd() const;
        void close_fd();
};
#endif