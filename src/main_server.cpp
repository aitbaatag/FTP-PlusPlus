#include "../inc/Server/server.hpp"

int main()
{
    char buffer[1024] = {0};
    Server Server(21);
    Server.StartServer();
    int client_fd = Server.get_client_fd();
    read(client_fd, buffer, 1024);
    std::cout << buffer << std::endl;
    return 0;
}