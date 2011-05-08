#include "../address.hh"
#include "../type.hh"
#include "../utils.hh"
#include "syscall-get-char-pos.hh"

namespace cscript { namespace skit { namespace syscalls {

void skit_get_char_pos(skit_cscript& script,
                       const std::vector<uint32_t>& args)
{
    float& x = *((float*)address::get_ptr(script, args[1]));
    float& y = *((float*)address::get_ptr(script, args[2]));
    script.backend().get_char_pos(args[0], x, y);

    variable& v = script.curr_thread().scratch.top(0);
    v.value.u32 = 0;
    v.address = 0;
    v.type = type::IMMEDIATE | type::SWORD;
    script.curr_thread().scratch.push();
}

}}}
