#include "../cscript.hh"
#include "../instruction-register.hh"
#include "../type.hh"

namespace cscript { namespace instruction {

void load_schar_handler(cscript& interp, uint32_t opcode)
{
    variable& var = interp.curr_thread().scratch.top(0);
    var.value.u32 = (int8_t)(opcode & 0xFF);
    var.address = 0;
    var.type = type::IMMEDIATE | type::SCHAR;
    interp.curr_thread().scratch.push();
}

register_instruction load_schar_instr(0x02030000, 0xFFFF0000,
                                      load_schar_handler);

}}
