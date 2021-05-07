#ifndef IO_H
#define IO_H

#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include "werror.h"

struct File
{
    std::string path;
    std::string data;
};

struct IO
{
    WError werror;
    std::vector<File> reads;
    IO(WError wError) : werror(wError){};
    void read(std::string path);
    void write(File file);
};

#endif