#include "../cscript.hh"
#include "../instruction-register.hh"

namespace cscript { namespace instruction {

void rawidx_handler(cscript& interp, uint32_t opcode)
{
    uint32_t arg = interp.read_code_at(interp.curr_thread().pc++);
    uint16_t idx = arg & 0xFFFF;
    uint16_t elem_size = arg >> 16;
    uint8_t elem_type = opcode & 0xFF;

    variable& var = interp.curr_thread().scratch.top(1);
    var.address += idx;
    var.type = (var.type & 0xFF00) | elem_type;
    var.pointed_size = elem_size;
    var.value.u32 = var.read_value_from_addr(interp);
}

register_instruction rawidx_instr(0x012A0000, 0xFFFF0000, rawidx_handler);

}}
