#ifndef CMDHANDLER_HPP
#define CMDHANDLER_HPP

#include <iostream>
#include <sstream>
#include "FileHandler.hpp"
#define UPLOAD "upload"
#define DOWNLOAD "download"
#define LIST "LIST"
#define CWD "CWD"
#define PWD "PWD"
#define EXIT "exit"
#define CBUFF_SIZE 256

class Cmdhandler {
private:
  std::string cmd;
  std::string fileName;
  int client_fd;
  char buffer[256];
public:
  Cmdhandler();
  void GetCmd();
  void ProcessCmd();
  void setFdClient(int client_fd);
  
};
#endif // !CMDHANDLER_HPP

