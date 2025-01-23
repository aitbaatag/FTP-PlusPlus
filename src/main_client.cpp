#include "../../inc/Client/client.hpp"
#include <iostream>

int main()
{
    Client client(21);
    std::string cmd;

    client.CreateSocket();
    client.InitSocketAdd();
    client.ConnectToServer();
    std::cin >> cmd;
    send(client.Get_sockfd(), cmd.c_str(), cmd.size(), 0 );
    client.close_fd();
}