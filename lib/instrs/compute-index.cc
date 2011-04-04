#include "../cscript.hh"
#include "../instruction-register.hh"
#include "../type.hh"

namespace cscript { namespace instruction {

void idx_handler(cscript& interp, uint32_t opcode)
{
    (void)opcode;

    variable& idx = interp.curr_thread().scratch.top(1);
    variable& arr = interp.curr_thread().scratch.top(2);
    interp.curr_thread().scratch.pop();

    if (arr.type & type::POINTER)
    {
        uint32_t addr = arr.value.u32 + idx.value.u32 * arr.pointed_size;

        arr.type &= 0xF;
        arr.address = addr;
        arr.value.u32 = arr.read_value_from_addr(interp);
    }
    else if (arr.type & type::POINTER2)
    {
        throw exception("IDX: not yet implemented for POINTER2");
    }
    else
    {
        throw exception("IDX: indexing a non pointer type");
    }
}

register_instruction idx_instr(0x01260000, 0xFFFF0000, idx_handler);

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
