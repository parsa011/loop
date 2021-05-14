#include "console.h"

void console::fmtOSCmp()
{
#ifdef _WIN32
    result = std::regex_replace(stream.str(), std::regex("\033(.*)m"), "");
#else
    result = stream.str();
#endif
}

cOut::~cOut()
{
    fmtOSCmp();
    std::cout << result;
}

cErr::~cErr()
{
    fmtOSCmp();
    std::cerr << result;
}