#include "basic-cscript.hh"

#include <sstream>

namespace cscript {

void basic_cscript::handle_syscall(uint16_t syscall,
                                   const std::vector<uint32_t>& args)
{
    if (handle_common_syscall(syscall, args))
        return;

    std::ostringstream oss;

    oss << "error: a basic cscript can't handle syscall 0x";
    oss << std::hex << std::setfill('0') << std::setw(4);
    oss << syscall << std::endl;

    throw exception(oss.str());
}

}
