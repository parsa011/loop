#include "io.h"

void IO::read(std::string path)
{
    if (!std::filesystem::exists(path))
    {
        werror.compilerError(E_FILE_NOT_FOUND, "Expected File Does not Exists");
        exit(1);
    }
    else if (std::filesystem::is_directory(path))
    {
        werror.compilerError(E_IS_DIRECTORY, "Expected File Is A Directory");
        exit(1);
    }
    else if (!std::filesystem::is_regular_file(path))
    {
        werror.compilerError(E_IST_REGULAR_FILE, "Expected File Is't Regular");
        exit(1);
    }

    File file;
    std::stringstream content;
    std::ifstream in(path);
    content << in.rdbuf();
    in.close();

    file.path = path;
    file.data = content.str();
    reads.push_back(file);
}