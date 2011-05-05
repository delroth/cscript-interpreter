#include "../cscript.hh"
#include "../instruction-register.hh"
#include "../type.hh"
#include "../variable.hh"

namespace cscript { namespace instruction {

void post_incr_handler(cscript& interp, uint32_t opcode)
{
    (void)opcode;

    variable& var = interp.curr_thread().scratch.top(1);
    if (!type::trivially_integer(var.type))
        throw exception("incrementing a non integer variable");

    uint16_t increment = 1;
    if (var.type & type::POINTER)
        increment = var.pointed_size;
    else if (var.type & type::POINTER2)
        increment = 4;

    var.value.u32 += increment;
    var.write_value_to_addr(interp);
    var.value.u32 -= increment;
}

register_instruction post_incr_instr(0x01010000, 0xFFFF0000, post_incr_handler);

}}
