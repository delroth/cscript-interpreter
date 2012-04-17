#include "../address.hh"
#include "../type.hh"
#include "../utils.hh"
#include "syscall-set-char-pos.hh"

namespace cscript { namespace tos2_skit { namespace syscalls {

void skit_set_char_pos(tos2_skit_cscript& script,
                       const std::vector<uint32_t>& args)
{
    uint32_t id = args[0];
    float x = utils::float_from_u32(args[1]);
    float y = utils::float_from_u32(args[2]);
    uint32_t n = args[3];

    script.backend().set_char_pos(id, x, y, n);

    variable& v = script.curr_thread().scratch.top(0);
    v.value.u32 = 0;
    v.address = 0;
    v.type = type::IMMEDIATE | type::SWORD;
    script.curr_thread().scratch.push();
}

}}}
