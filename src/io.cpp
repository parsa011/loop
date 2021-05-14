#include "io.h"

void IO::read(const char *path)
{
    if (!std::filesystem::exists(path))
    {
        werror.compilerError(E_FILE_NOT_FOUND, "Expected File Does not Exists");
    }
    else if (std::filesystem::is_directory(path))
    {
        werror.compilerError(E_IS_DIRECTORY, "Expected File Is A Directory");
    }
    else if (!std::filesystem::is_regular_file(path))
    {
        werror.compilerError(E_IST_REGULAR_FILE, "Expected File Is't Regular");
    }

    std::string content;
    std::ifstream file(path);
    file.seekg(0, std::ios::end);
    content.resize((size_t)file.tellg());
    file.seekg(0);
    file.read(content.data(), (int)content.size());
    file.close();

    reads.push_back({path, content});
}