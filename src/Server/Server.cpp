#include "../../inc/Server/server.hpp"

Server::Server(int port)
{
    socket = new Socket(port);
}

Server::~Server()
{
    delete socket;
}

void Server::StartServer()
{
    socket->CreateSocket();
    socket->InitSocketAdd();
    socket->BindSocket();
    socket->ListenSocket();
    socket->AcceptConnection();
}

int Server::get_client_fd() const
{
    return socket->get_client_fd();
}