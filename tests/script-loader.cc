#include "script-loader.hh"

#include <boost/iostreams/device/mapped_file.hpp>

namespace cscript { namespace tests {

script_loader::script_loader(const std::string& file)
{
    std::string filename = SOURCE_DIR;
    filename += "/";
    filename += file;

    boost::iostreams::mapped_file_source src(filename);
    interp.parse_bytecode(src.data(), src.size());
}

}}
