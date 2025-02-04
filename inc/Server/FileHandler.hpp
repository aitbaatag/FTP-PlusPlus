#ifndef FILEHHANDLER_HPP
#define FILEHHANDLER_HPP

#include <iostream>
#include <filesystem>
#include <fstream>
#define BUFF_SIZE 1024
class FileHandler {
  private:
    std::ofstream File;
    std::string storagePath = "/home/user/ftp_storage/";
  public:
    FileHandler();
    ~FoileHnaler();
    int CreateFile();
    bool UPLOADD();
    bool DOWNLOAD();
    void ListFiles();
}
#endif
