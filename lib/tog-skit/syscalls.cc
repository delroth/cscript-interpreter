#include "syscalls.hh"
#include "syscall-unknown.hh"

#include <map>

namespace cscript { namespace tog_skit {

typedef std::function<void(tog_skit_cscript&,
                      const std::vector<uint32_t>&)> handler;

std::map<uint16_t, handler> handlers = {
    { syscalls::SKIT_UNKNOWN1_ID, syscalls::skit_unknown1 },
    { syscalls::SKIT_UNKNOWN2_ID, syscalls::skit_unknown2 },
    { syscalls::SKIT_UNKNOWN3_ID, syscalls::skit_unknown3 },
};

bool execute_syscall(cscript& script, uint16_t syscall,
                     const std::vector<uint32_t>& args)
{
    std::cout << "Executing syscall " << std::hex << syscall << " with args: ";
    for (auto arg : args)
    {
        std::cout << std::hex << std::setw(8) << std::setfill('0') << arg;
        std::cout << " ";
    }
    std::cout << std::endl;

    if (handlers.find(syscall) == handlers.end())
        return false;

    try
    {
        tog_skit_cscript& skit_script = dynamic_cast<tog_skit_cscript&>(script);
        handlers[syscall](skit_script, args);
    }
    catch (const std::bad_cast&)
    {
        throw exception("Executing a skit syscall on a non-skit cscript");
    }

    return true;
}

}}
