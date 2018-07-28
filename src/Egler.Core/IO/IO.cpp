#include <fstream>
#include <sstream>
#include "IO.hpp"

namespace Egler::IO
{
    std::string ReadAllText(const char * const fileName)
    {
        CheckPtr(fileName);

        std::ifstream file(fileName);
        if(!file.good())
        { throw FailureException("Failed to open file at '%s'.", fileName); }

        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();

        return buffer.str();
    }
}