#include "../address.hh"
#include "../cscript.hh"
#include "../instruction-register.hh"
#include "../type.hh"
#include "../variable.hh"

namespace cscript { namespace instruction {

void load_addr_handler(cscript& interp, uint32_t opcode)
{
    bool load_stack = (opcode & 0xFF000000) == 0x03000000;
    uint32_t offset = interp.read_code_at(interp.curr_thread().pc++);
    uint8_t type = (opcode >> 16) & 0xFF;
    variable& var = interp.curr_thread().scratch.top(0);

    uint32_t addr;
    if (load_stack)
    {
        int32_t s_offset = (int32_t)offset;
        if (s_offset % 4 != 0)
            throw exception("load_stack_addr: misaligned offset");
        s_offset /= 4;
        offset = interp.curr_thread().stk.frame_base() - s_offset;
        addr = address::make_stack_addr(interp.curr_thread_id(), offset);
    }
    else
    {
        addr = address::make_data_addr(offset);
    }

    if (type & type::POINTER3)
    {
        var.address = 0;
        var.value.u32 = addr;
        var.type = type::IMMEDIATE | (type & 0xF);
    }
    else
    {
        var.address = addr;
        var.type = type;
        var.value.u32 = var.read_value_from_addr(interp);
    }

    interp.curr_thread().scratch.push();
}

register_instruction load_stack_addr_instr(0x03000000, 0xFF000000,
                                           load_addr_handler);

register_instruction load_data_addr_instr(0x04000000, 0xFF000000,
                                          load_addr_handler);

}}
