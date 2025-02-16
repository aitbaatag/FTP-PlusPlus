#include "../inc/Client/Client.hpp"
#include <iostream>

int main() {
  const std::string &ip = "127.0.0.1";

  Client client("127.0.0.1", 2000);

  client.CreateTCPIpv4Socket();
  client.InitSocketAdd();
  client.ConnectToServer();
}
