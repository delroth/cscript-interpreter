#include "skit-cscript.hh"
#include "skit/syscalls.hh"

#include <sstream>

namespace cscript {

void skit_cscript::handle_syscall(uint16_t syscall)
{
    if (!skit::execute_syscall(*this, syscall))
    {
        std::ostringstream oss;

        oss << "error: syscall 0x";
        oss << std::hex << std::setfill('0') << std::setw(4);
        oss << syscall << " not yet implemented" << std::endl;

        throw exception(oss.str());
    }
}

}
