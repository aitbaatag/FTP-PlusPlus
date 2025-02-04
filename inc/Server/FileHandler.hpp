#ifndef FILEHHANDLER_HPP
#define FILEHHANDLER_HPP

#include <iostream>
#include <filesystem>
#include <fstream>
#include <cstring>
#define BUFF_SIZE 1024
class FileHandler {
  private:
    std::string storagePath;

    bool OpenFile(const std::string &filepath);
    bool fileExists(const std::string &filepath);
  public:
    FileHandler(int client_fd);
    bool UPLOADD(int client_fd, const std::string& fileName);
    bool DOWNLOAD(int client_fd, const std::string& fileName);
    // void ListFiles(); // TODO
}
#endif
