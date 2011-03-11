#include "cscript.hh"

#include <boost/iostreams/device/mapped_file.hpp>
#include <cstdio>
#include <string>

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <script.so>\n", argv[0]);
        return 1;
    }

    std::string filename = argv[1];
    boost::iostreams::mapped_file_source src(filename);

    cscript::cscript script;
    if (!script.parse_bytecode(src.data(), src.size()))
    {
        fprintf(stderr, "error: %s is not a valid bytecode\n", argv[1]);
        return 2;
    }

    return 0;
}
