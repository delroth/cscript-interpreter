#include "syscalls.hh"
#include "syscall-init.hh"
#include "syscall-say.hh"
#include "syscall-unknown.hh"
#include "syscall-wait.hh"

#include <map>

namespace cscript { namespace skit {

typedef std::function<void(cscript&, const std::vector<uint32_t>&)> handler;
std::map<uint16_t, handler> handlers = {
    { syscalls::SKIT_INIT_ID, syscalls::skit_init },
    { syscalls::SKIT_WAIT_ID, syscalls::skit_wait },
    { syscalls::SKIT_UNKNOWN1_ID, syscalls::skit_unknown1 },
    { syscalls::SKIT_UNKNOWN2_ID, syscalls::skit_unknown2 },
    { syscalls::SKIT_UNKNOWN3_ID, syscalls::skit_unknown3 },
    { syscalls::SKIT_UNKNOWN4_ID, syscalls::skit_unknown4 },
    { syscalls::SKIT_UNKNOWN5_ID, syscalls::skit_unknown5 },
    { syscalls::SKIT_SAY_ID, syscalls::skit_say },
};

bool execute_syscall(cscript& script, uint16_t syscall,
                     const std::vector<uint32_t>& args)
{
    if (handlers.find(syscall) == handlers.end())
        return false;
    handlers[syscall](script, args);
    return true;
}

}}
