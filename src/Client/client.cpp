#include "../../inc/Client/Client.hpp"

Client::Client(int port) : Socket(port)
{

}
Client::~Client()
{
}
void Client::ConnectToServer()
{
    if (connect(sockfd, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "Failed to connect to the server\n";
        exit (1);
    }
    std::cout << "Successfully connected to the server\n";




    // Continuous communication loop
    char buffer[1024];
    while (true) {
        // Send a message to the server
        std::cout << "Enter message to send (type 'exit' to disconnect): ";
        std::string message;
        std::getline(std::cin, message);
        if (message == "exit") {
            std::cout << "Disconnecting from the server...\n";
            break;
        }

        write(sockfd, message.c_str(), message.size());

        // Receive response from the server
        memset(buffer, 0, sizeof(buffer)); // Clear the buffer
        int bytes_read = read(sockfd, buffer, sizeof(buffer) - 1);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0'; // Null-terminate the string
            std::cout << "Received from server: " << buffer << std::endl;
        } else {
            std::cerr << "Error reading from server\n";
            break; // Exit loop on error
        }
    }

    // Close the connection when done
    close(sockfd);
}
int Client::Get_sockfd() const
{
    return sockfd;
}
