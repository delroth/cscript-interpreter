#include "syscalls.hh"
#include "syscall-init.hh"
#include "syscall-wait.hh"

#include <map>

namespace cscript { namespace skit {

std::map<uint16_t, std::function<void(cscript&)>> handlers = {
    { syscalls::SKIT_INIT_ID, syscalls::skit_init },
    { syscalls::SKIT_WAIT_ID, syscalls::skit_wait }
};

bool execute_syscall(cscript& script, uint16_t syscall)
{
    if (handlers.find(syscall) == handlers.end())
        return false;
    handlers[syscall](script);
    return true;
}

}}
