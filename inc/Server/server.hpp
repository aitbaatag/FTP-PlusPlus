#ifndef SERVER_HPP
#define SERVER_HPP

#include "../Socket/Socket.hpp"

class Server
{
    private:
        Socket *socket;
    public:
        Server(int port);
        ~Server();
        void StartServer();
        int get_client_fd() const;
};
#endif