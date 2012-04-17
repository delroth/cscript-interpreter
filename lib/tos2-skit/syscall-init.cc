#include "../address.hh"
#include "../type.hh"
#include "syscall-init.hh"

#include <string>

namespace cscript { namespace tos2_skit { namespace syscalls {

void skit_init(tos2_skit_cscript& script, const std::vector<uint32_t>& args)
{
    std::string skit_id = address::get_ptr(script, args[0]);
    script.backend().init(skit_id);

    variable& v = script.curr_thread().scratch.top(0);

    v.value.u32 = 0;
    v.address = 0;
    v.type = type::IMMEDIATE | type::SWORD;

    script.curr_thread().scratch.push();
}

}}}
