#ifndef FILEHHANDLER_HPP
#define FILEHHANDLER_HPP

#include <iostream>
#include <filesystem>
#include <fstream>
#include <cstring>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <sys/types.h>
#define BUFF_SIZE 1024
class FileHandler {
  private:
    std::string storagePath;

    bool OpenFile(std::fstream &file, const std::string &filepath, std::ios_base::openmode mode);
    bool fileExists(const std::string &filepath);
  public:
    FileHandler(const std::string &storagePath);
    bool UPLOAD(int client_fd, const std::string& fileName);
    bool DOWNLOAD(int client_fd, const std::string& fileName);
    // void ListFiles();
};
#endif
