#include "../inc/Client/Client.hpp"
#include <iostream>

int main()
{
    Client client(21);
    std::string cmd;

    client.CreateSocket();
    client.InitSocketAdd();
    client.ConnectToServer();
}
