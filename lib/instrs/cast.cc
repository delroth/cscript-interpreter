#include "../cscript.hh"
#include "../instruction-register.hh"
#include "../variable.hh"
#include "../type.hh"

namespace cscript { namespace instruction {

void cast_handler(cscript& interp, uint32_t opcode)
{
    uint8_t dest_type = opcode & 0xFF;

    variable& v = interp.curr_thread().scratch.top(0);
    v.value.u32 = v.cast_to(dest_type);
    v.type = (v.type & 0xFF00) | dest_type;
}

register_instruction cast_instr(0x01290000, 0xFFFF0000, cast_handler);

}}
