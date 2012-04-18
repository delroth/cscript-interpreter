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

cscript::cscript* new_default_cscript(const char* data, size_t size,
                                      const std::vector<std::string>& args)
{
    (void)args;

    return new cscript::basic_cscript(data, size);
}

cscript::cscript* new_tos2_skit_cscript(const char* data, size_t size,
                                        const std::vector<std::string>& args)
{
    (void)args;

    frontend::tos2_skit::backend* back = new frontend::tos2_skit::backend();
    return new cscript::tos2_skit_cscript(back, data, size);
}

cscript::cscript* new_tog_skit_cscript(const char* data, size_t size,
                                       const std::vector<std::string>& args)
{
    if (args.size() < 1)
        throw cscript::exception("missing argument: scs file path");

    frontend::tog_skit::backend* back = new frontend::tog_skit::backend(
        args[0]
    );
    return new cscript::tog_skit_cscript(back, data, size);
}

std::map<
    std::string,
    std::function<cscript::cscript*(const char*, size_t,
                                    const std::vector<std::string>&)>
> cscript_handlers = {
    { "default", new_default_cscript },
    { "tos2-skit", new_tos2_skit_cscript },
    { "tog-skit", new_tog_skit_cscript },
};

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        fprintf(stderr, "usage: %s <type> <script.so> [args...]\n", argv[0]);
        fprintf(stderr, "supported script types:\n");
        for (auto p : cscript_handlers)
            fprintf(stderr, " - %s\n", p.first.c_str());
        return 1;
    }

    std::string script_type = argv[1];
    std::string filename = argv[2];
    std::vector<std::string> additional_args(argv + 3, argv + argc);
    boost::iostreams::mapped_file_source src(filename);

    if (cscript_handlers.find(script_type) == cscript_handlers.end())
    {
        std::cerr << "error: invalid script type " << script_type << std::endl;
        return 4;
    }

    try
    {
        auto handler = cscript_handlers[script_type];
        std::shared_ptr<cscript::cscript> scr(
            handler(src.data(), src.size(), additional_args)
        );
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
