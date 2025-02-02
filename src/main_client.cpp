#include "../inc/Client/Client.hpp"
#include <iostream>

int main()
{
    Client client(21);
    std::string cmd;

    client.CreateTCPIpv4Socket();
    client.InitSocketAdd();
    client.ConnectToServer();
}
