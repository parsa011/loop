#ifndef CONSOLE_H
#define CONSOLE_H
#include <sstream>

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


inline cOut out{};
inline cErr outerr{};

#endif
