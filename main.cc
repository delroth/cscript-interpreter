#include "cscript.hh"

#include <boost/iostreams/device/mapped_file.hpp>
#include <cstdio>
#include <iostream>
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

    try
    {
        cscript::cscript script(src.data(), src.size());
    }
    catch (const cscript::bad_script_exception& ex)
    {
        std::cerr << "error: " << ex.message() << std::endl;
        return 2;
    }

    return 0;
}
