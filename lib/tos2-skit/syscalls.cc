#include "syscalls.hh"
#include "syscall-get-char-pos.hh"
#include "syscall-init.hh"
#include "syscall-init-char.hh"
#include "syscall-say.hh"
#include "syscall-set-char-pos.hh"
#include "syscall-unknown.hh"
#include "syscall-wait.hh"

#include <map>

namespace cscript { namespace tos2_skit {

typedef std::function<void(tos2_skit_cscript&,
                      const std::vector<uint32_t>&)> handler;

std::map<uint16_t, handler> handlers = {
    { syscalls::SKIT_INIT_ID, syscalls::skit_init },
    { syscalls::SKIT_WAIT_START_ID, syscalls::skit_wait_start },

    { syscalls::SKIT_INIT_CHAR_ID, syscalls::skit_init_char },
    { syscalls::SKIT_GET_CHAR_POS_ID, syscalls::skit_get_char_pos },
    { syscalls::SKIT_SET_CHAR_POS_ID, syscalls::skit_set_char_pos },

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
    { syscalls::SKIT_UNKNOWN12_ID, syscalls::skit_unknown12 },
    { syscalls::SKIT_SAY_ID, syscalls::skit_say },
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
        tos2_skit_cscript& skit_script = dynamic_cast<tos2_skit_cscript&>(script);
        handlers[syscall](skit_script, args);
    }
    catch (const std::bad_cast&)
    {
        throw exception("Executing a skit syscall on a non-skit cscript");
    }

    return true;
}

}}
