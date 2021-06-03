#include <loop/utils.hpp>

std::vector<std::string> utils::split(const std::string &str, const std::string &delim) {
    std::string::size_type b = 0;
    std::vector<std::string> result;

    while ((b = str.find_first_not_of(delim, b)) != std::string::npos) {
        size_t e = str.find_first_of(delim, b);
        result.push_back(str.substr(b, e - b));
        b = e;
    }
    return result;
}
