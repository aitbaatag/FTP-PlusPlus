#ifndef CMDHANDLER_HPP
#define CMDHANDLER_HPP

#include <iostream>
#include <sstream>
#include "fileHandler.hpp"
#define UPLOAD "UPLOAD"
#define DOWNLOAD "DOWNLOAD"
#define EXIT "EXIT"
#define BUFF_SIZE 256

class Cmdhandler {
pravite:
  std::string cmd;
  std::string fileName;
  int client_fd;
  char buffer[256];
public:
  Cmdhandler();
  ~Cmdhandler();
  void GetCmd();
  void ProcessCmd();
  
};
#endif // !CMDHANDLER_HPP

