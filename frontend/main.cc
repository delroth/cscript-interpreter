#include "tog-skit-backend.hh"
#include "tos2-skit-backend.hh"

#include <basic-cscript.hh>
#include <tos2-skit-cscript.hh>
#include <tog-skit-cscript.hh>

#include <boost/iostreams/device/mapped_file.hpp>
#include <cstdio>
#include <iostream>
#include <map>
#include <memory>
#include <string>

cscript::cscript* new_default_cscript(const char* data, size_t size)
{
    return new cscript::basic_cscript(data, size);
}

cscript::cscript* new_tos2_skit_cscript(const char* data, size_t size)
{
    frontend::tos2_skit::backend* back = new frontend::tos2_skit::backend();
    return new cscript::tos2_skit_cscript(back, data, size);
}

cscript::cscript* new_tog_skit_cscript(const char* data, size_t size)
{
    frontend::tog_skit::backend* back = new frontend::tog_skit::backend();
    return new cscript::tog_skit_cscript(back, data, size);
}

std::map<
    std::string,
    std::function<cscript::cscript*(const char*, size_t)>
> cscript_handlers = {
    { "default", new_default_cscript },
    { "tos2-skit", new_tos2_skit_cscript },
    { "tog-skit", new_tog_skit_cscript },
};

int main(int argc, char** argv)
{
    if (argc != 2 && argc != 3)
    {
        fprintf(stderr, "usage: %s [type] <script.so>\n", argv[0]);
        fprintf(stderr, "supported script types:\n");
        for (auto p : cscript_handlers)
            fprintf(stderr, " - %s\n", p.first.c_str());
        return 1;
    }

    std::string script_type = argc == 3 ? argv[1] : "default";
    std::string filename = argc == 3 ? argv[2] : argv[1];
    boost::iostreams::mapped_file_source src(filename);

    if (cscript_handlers.find(script_type) == cscript_handlers.end())
    {
        std::cerr << "error: invalid script type " << script_type << std::endl;
        return 4;
    }

    try
    {
        auto handler = cscript_handlers[script_type];
        std::shared_ptr<cscript::cscript> scr(handler(src.data(), src.size()));
        try
        {
            scr->run();
        }
        catch (const cscript::exception& ex)
        {
            std::cerr << scr->curr_thread() << std::endl;
            std::cerr << "runtime error: " << ex.message() << std::endl;
            return 3;
        }
    }
    catch (const cscript::exception& ex)
    {
        std::cerr << "load error: " << ex.message() << std::endl;
        return 2;
    }

    return 0;
}
