#include "../../inc/Server/Cmdhandler.hpp"

Cmdhandler::Cmdhandler(int client_fd) : buffer({0})
{
  this->client_fd = client_fd;
}
void Cmdhandler::GetCmd()
{
  int valread;

  valread = recv(client_fd, buffer, SIZE_BUFF, 0);
  if (valread < 0)
  {
    perror("Recv failed");
    exit(EXIT_FAILURE);
  }
  cmd(buffer);
}
void Cmdhandler::ProcessCmd()
{
  if (cmd.compare(UPLOAD) == 0)
  else if (cmd.compare(DOWNLOAD) == 0)
  else if (cmd.compare(EXIT) == 0)
  else

}
