#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <iostream>
#include <filesystem>
#include <fstream>
#include <cstring>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unordered_map>
#include <unistd.h>
#include <fcntl.h>
namespace fs = std::filesystem;
#define BUFF_SIZE 1024
class FileManager {
  private:
    int fdsocket;

    bool openfile(std::fstream& file, fs::path filepath, std::ios_base::openmode mode);
    bool fileexists(const std::string& filepath);
  public:
    FileManager(int fdsocket);
    void download(const std::string &filename);
    void upload(const std::string &filename);
};
#endif
