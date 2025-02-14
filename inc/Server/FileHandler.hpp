#ifndef FILEHHANDLER_HPP
#define FILEHHANDLER_HPP

#include "../../inc/DataConnection/ServerDataConnection.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <fcntl.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <unordered_map>
namespace fs = std::filesystem;
#define BUFF_SIZE 1024
class FileHandler {
private:
  fs::path current_dir;
  fs::path new_path;

  bool OpenFile(std::fstream &file, fs::path filepath,
                std::ios_base::openmode mode, int client_fd);
  bool fileExists(const std::string &filepath);

public:
  FileHandler();
  bool uPLOAD(int client_fd, const std::string &fileName);
  bool dOWNLOAD(int client_fd, const std::string &fileName);
  void ChangeDirectory(int client_fd, const std::string &new_dir);
  void SendResponse(int client_fd, const std::string &response);
  void ListFiles(int client_fd);
  fs::path GetCurrent_dir() const;
};
#endif
