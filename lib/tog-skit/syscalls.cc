#include "../type.hh"

#include "syscalls.hh"
#include "syscall-random.hh"
#include "syscall-strings.hh"
#include "syscall-unknown.hh"

#include <iostream>
#include <map>

namespace cscript { namespace tog_skit {

typedef std::function<int32_t(tog_skit_cscript&,
                      const std::vector<uint32_t>&)> handler;

std::map<uint16_t, handler> handlers = {
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

    { syscalls::SKIT_GET_STRING, syscalls::skit_get_string },

    { syscalls::SKIT_RANDOM, syscalls::skit_random },
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
        int32_t ret = handlers[syscall](skit_script, args);

        variable& v = script.curr_thread().scratch.top(0);
        v.value.u32 = ret;
        v.address = 0;
        v.type = type::IMMEDIATE | type::SWORD;
        script.curr_thread().scratch.push();
    }
    catch (const std::bad_cast&)
    {
        throw exception("Executing a skit syscall on a non-skit cscript");
    }

    return true;
}

}}
