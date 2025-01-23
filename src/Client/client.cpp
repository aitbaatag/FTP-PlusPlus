#include "../../inc/Client/client.hpp"

Client::Client(int port)
{
    this->port = port;
}
void Client::CreateSocket()
{
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        std::cerr << "Failed to create socket\n";
        exit(1);
    }
}
void Client::InitSocketAdd()
{
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    // Convert string IP to binary
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        std::cerr << "Invalid IP address\n";
        exit(1);
    }
}
void Client::ConnectToServer()
{
    if (connect(sockfd, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "Failed to connect to the server\n";
        exit (1);
    }
    std::cout << "Connected to the server\n";
    exit (0);
}
int Client::Get_sockfd() const
{
    return (port);
}
void Client::close_fd()
{
    close (sockfd);
}