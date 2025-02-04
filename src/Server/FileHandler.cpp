#include "../../inc/Server/FileHandler.hpp"

FileHandler::FileHandler(const std::string& storagePath) : storagePath(storagePath) {
    std::filesystem::create_directories(storagePath);
}

bool FileHandler::OpenFile(std::fstream& file, const std::string& filepath, std::ios_base::openmode mode) {
    file.open(filepath, mode);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filepath << std::endl;
        return false;
    }
    return true;
}

bool FileHandler::fileExists(const std::string& filepath) {
    return std::filesystem::exists(filepath);
}

bool FileHandler::UPLOAD(int client_fd, const std::string& fileName) {
    std::string filepath = storagePath + fileName;

    if (fileExists(filepath)) {
        send(client_fd, "ERROR: File already exists\n", 27, 0);
        return false;
    }

    std::fstream file;
    if (!OpenFile(file, filepath, std::ios::binary | std::ios::out)) {
        send(client_fd, "ERROR: Unable to create file\n", 28, 0);
        return false;
    }

    char buffer[BUFF_SIZE];
    size_t totalBytes = 0;

    while (true) {
        int valread = recv(client_fd, buffer, BUFF_SIZE, 0);
        if (valread < 0) {
            send(client_fd, "ERROR: File transfer failed\n", 27, 0);
            file.close();
            return false;
        } else if (valread == 0) {
            break; // End of file
        }
        file.write(buffer, valread);
        totalBytes += valread;
    }

    file.close();
    send(client_fd, "SUCCESS: File uploaded\n", 23, 0);
    return true;
}

bool FileHandler::DOWNLOAD(int client_fd, const std::string& fileName) {
    std::string filepath = storagePath + fileName;

    if (!fileExists(filepath)) {
        send(client_fd, "ERROR: File not found\n", 22, 0);
        return false;
    }

    std::fstream file;
    if (!OpenFile(file, filepath, std::ios::binary | std::ios::in)) {
        send(client_fd, "ERROR: Unable to open file\n", 26, 0);
        return false;
    }

    char buffer[BUFF_SIZE];
    size_t totalBytes = 0;

    while (!file.eof()) {
        file.read(buffer, sizeof(buffer));
        int valread = file.gcount();
        if (valread > 0) {
            if (send(client_fd, buffer, valread, 0) < 0) {
                file.close();
                return false;
            }
            totalBytes += valread;
        }
    }

    file.close();
    send(client_fd, "SUCCESS: File downloaded\n", 25, 0);
    return true;
}
