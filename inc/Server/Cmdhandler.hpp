#ifndef CMDHANDLER_HPP
#define CMDHANDLER_HPP

#include <iostream>
#include "fileHandler.hpp"
#define UPLOAD "UPLOAD"
#define DOWNLOAD "DOWNLOAD"
#define EXIT "EXIT"
#define SIZE_BUFF 256

class Cmdhandler {
pravite:
  std::string cmd;
  int client_fd;
  char buffer[256];
public:
  Cmdhandler();
  ~Cmdhandler();
  void GetCmd();
  void ProcessCmd();
  
};
#endif // !CMDHANDLER_HPP

