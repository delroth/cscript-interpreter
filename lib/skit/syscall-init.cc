#include "../type.hh"
#include "syscall-init.hh"

namespace cscript { namespace skit { namespace syscalls {

void skit_init(skit_cscript& script, const std::vector<uint32_t>& args)
{
    (void)args;

    // TODO: stub
    variable& v = script.curr_thread().scratch.top(0);

    v.value.u32 = 0;
    v.address = 0;
    v.type = type::IMMEDIATE | type::SWORD;

    script.curr_thread().scratch.push();
}

}}}
