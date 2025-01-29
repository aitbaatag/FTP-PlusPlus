#include "../../inc/Server/Server.hpp"

Server::Server(int port) :  Socket(port) 
{

}

Server::~Server()
{
    Server::~Socket();
}

void Server::StartServer()
{
    CreateSocket();
    InitSocketAdd();
    BindSocket();
    ListenSocket();
    std::cout << "Waiting for a connection...\n";
    AcceptConnection();
    std::cout << "Connection accepted\n";
    while (true)
    {

    // Communication loop with the connected client
    char buffer[1024];
    while (true) {
        memset(buffer, 0, sizeof(buffer)); // Clear the buffer
        int bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0'; // Null-terminate the string
            std::cout << "Received from client: " << buffer << std::endl;

            // Respond to the client
            std::string response = "I get : " + std::string(buffer);
            write(client_fd, response.c_str(), response.size());
        } else if (bytes_read == 0) {
            std::cout << "Client disconnected.\n";
            break; // Exit loop if the client disconnects
        } else {
            std::cerr << "Error reading from client\n";
            exit(1); // Exit loop on error
        }
    }

    // Close client socket after communication ends
    close(client_fd);
}
}
