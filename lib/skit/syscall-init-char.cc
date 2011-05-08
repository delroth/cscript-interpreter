#include "../address.hh"
#include "../type.hh"
#include "../utils.hh"
#include "syscall-init-char.hh"

namespace cscript { namespace skit { namespace syscalls {

void skit_init_char(skit_cscript& script, const std::vector<uint32_t>& args)
{
    uint32_t id = args[0];
    uint32_t face = args[1];
    float x = utils::float_from_u32(args[2]);
    float y = utils::float_from_u32(args[3]);
    uint32_t subface = args[4];

    script.backend().init_char(id, face, x, y, subface);

    variable& v = script.curr_thread().scratch.top(0);
    v.value.u32 = 0;
    v.address = 0;
    v.type = type::IMMEDIATE | type::SWORD;
    script.curr_thread().scratch.push();
}

}}}
