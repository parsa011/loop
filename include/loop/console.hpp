#ifndef CONSOLE_H
#define CONSOLE_H
#include <sstream>
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif

struct console
{
    std::ostringstream stream;
    std::string result;
    template <class generic>
    console &operator<<(generic const &msg)
    {
        stream << msg;
        return *this;
    };
    void fmtOSCmp();
};

struct cOut : console
{
    ~cOut();
};

struct cErr : console
{
    ~cErr();
};

#define out cOut()
#define outerr cErr()

#endif