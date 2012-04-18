#include "tog-skit-cscript.hh"
#include "tog-skit/syscalls.hh"

#include <sstream>

namespace cscript {

void tog_skit_cscript::handle_syscall(uint16_t syscall,
                                      const std::vector<uint32_t>& args)
{
    if (handle_common_syscall(syscall, args))
        return;

    if (!tog_skit::execute_syscall(*this, syscall, args))
    {
        std::ostringstream oss;

        oss << "error: " << args.size() << " args syscall 0x";
        oss << std::hex << std::setfill('0') << std::setw(4);
        oss << syscall << " not yet implemented" << std::endl;

        throw exception(oss.str());
    }
}

}
