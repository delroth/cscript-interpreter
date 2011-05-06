#include "../type.hh"
#include "syscall-unknown.hh"

namespace cscript { namespace skit { namespace syscalls {

void skit_unknown(cscript& script, const std::vector<uint32_t>& args)
{
    (void)args;

    // TODO: stub
    variable& v = script.curr_thread().scratch.top(0);

    v.value.u32 = 0;
    v.address = 0;
    v.type = type::IMMEDIATE | type::SWORD;

    script.curr_thread().scratch.push();
}

void skit_unknown2(cscript& script, const std::vector<uint32_t>& args)
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
