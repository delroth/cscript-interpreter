#include "../cscript.hh"
#include "../instruction-register.hh"

namespace cscript { namespace instruction {

void mov_handler(cscript& interp, uint32_t opcode)
{
    (void)opcode;
    variable& src = interp.curr_thread().scratch.top(1);
    variable& dst = interp.curr_thread().scratch.top(2);

    interp.curr_thread().scratch.pop();

    dst.value.u32 = src.cast_to(dst.type);
    dst.write_value_to_addr(interp);
}

register_instruction mov_instr(0x01090000, 0xFFFF0000, mov_handler);

}}
