#ifndef IO_H
#define IO_H

#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include "global.h"

struct File
{
    std::string path;
    std::string data;
};

struct IO
{
    std::fstream fStream;
    std::vector<File> reads;
    void read(const char *path);
    void write(File file);
};

#endif