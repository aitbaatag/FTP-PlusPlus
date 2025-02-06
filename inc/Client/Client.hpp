#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../Socket/Socket.hpp"
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include "FileManager.hpp"
#include <sstream>
class Client : public Socket {
private:
   const char *server_ip;

   struct Cinput {
     std::string filename;
     std::string cmd;
   };
public:
    Client(const char *server_ip, int port);
    ~Client();
    void ConnectToServer();
    int Get_sockfd() const;
    bool SendMessage(const std::string &message);
    std::string ReceiveMessage();
    Client::Cinput SplitInput(const std::string &input);
};
#endif // CLIENT_HPP

