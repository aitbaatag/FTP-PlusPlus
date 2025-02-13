#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include "../DataConnection/ClientDataConnection.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <fcntl.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
namespace fs = std::filesystem;
#define BUFF_SIZE 1024
class FileManager {
private:
  int fdsocket;
  const std::string &server_ip;

  bool openfile(std::fstream &file, fs::path filepath,
                std::ios_base::openmode mode);
  bool fileexists(const std::string &filepath);

public:
  FileManager(int fdsocket, const std::string &server_ip);
  void download(const std::string &filename);
  void upload(const std::string &filename);
};
#endif
