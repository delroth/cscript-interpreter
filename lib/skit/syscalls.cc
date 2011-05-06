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
    { syscalls::SKIT_WAIT2_ID, syscalls::skit_wait },
    { syscalls::SKIT_WAIT3_ID, syscalls::skit_wait },
    { syscalls::SKIT_WAIT4_ID, syscalls::skit_wait },
    { syscalls::SKIT_UNKNOWN1_ID, syscalls::skit_unknown1 },
    { syscalls::SKIT_UNKNOWN2_ID, syscalls::skit_unknown2 },
    { syscalls::SKIT_UNKNOWN3_ID, syscalls::skit_unknown3 },
    { syscalls::SKIT_UNKNOWN4_ID, syscalls::skit_unknown4 },
    { syscalls::SKIT_UNKNOWN5_ID, syscalls::skit_unknown5 },
    { syscalls::SKIT_UNKNOWN6_ID, syscalls::skit_unknown6 },
    { syscalls::SKIT_UNKNOWN7_ID, syscalls::skit_unknown7 },
    { syscalls::SKIT_UNKNOWN8_ID, syscalls::skit_unknown8 },
    { syscalls::SKIT_UNKNOWN9_ID, syscalls::skit_unknown9 },
    { syscalls::SKIT_UNKNOWN10_ID, syscalls::skit_unknown10 },
    { syscalls::SKIT_UNKNOWN11_ID, syscalls::skit_unknown11 },
    { syscalls::SKIT_SAY_ID, syscalls::skit_say },
    { syscalls::SKIT_INITSOMETHING_ID, syscalls::skit_initsomething },
    { syscalls::SKIT_GETSOMETHING_ID, syscalls::skit_getsomething },
    { syscalls::SKIT_SETSOMETHING_ID, syscalls::skit_setsomething },
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
