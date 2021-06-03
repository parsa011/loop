#ifndef IO_H
#define IO_H
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include "global.hpp"

struct File {
    std::string path;
    std::string data;
};

struct IO {
    std::fstream fStream;
    std::vector<File> reads;
    void read(const char *path);
    void write(File file);
};

#endif
