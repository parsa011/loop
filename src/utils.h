#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <iostream>
#include <vector>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

namespace utils
{
    std::vector<std::string> split(const std::string &str, const std::string &delim);
}

#endif