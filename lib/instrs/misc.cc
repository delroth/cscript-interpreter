#include "../cscript.hh"
#include "../instruction-register.hh"
#include "../type.hh"

namespace cscript { namespace instruction {

void nop_handler(cscript& interp, uint32_t opcode)
{
    // Still can't understand why the compiler generates this...
    // Maybe in an older version it did something.

    (void)interp;
    (void)opcode;
}

register_instruction nop_instr(0x01060000, 0xFFFF0000, nop_handler);

void exit_handler(cscript& interp, uint32_t opcode)
{
    (void)opcode;
    interp.exit();
}

register_instruction exit_instr(0x07000000, 0xFF000000, exit_handler);

void forcetype_handler(cscript& interp, uint32_t opcode)
{
    uint16_t new_type = type::IMMEDIATE | ((opcode >> 16) & 0xFF);
    uint16_t elem_size = opcode & 0xFFFF;

    variable& var = interp.curr_thread().scratch.top(0);
    var.type = new_type;
    var.pointed_size = elem_size;
}

register_instruction forcetype_instr(0x14000000, 0xFF000000,
                                     forcetype_handler);

}}
