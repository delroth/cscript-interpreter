#include "../cscript.hh"
#include "../instruction-register.hh"

namespace cscript { namespace instruction {

void reserve_handler(cscript& interp, uint32_t opcode)
{
    (void)opcode;

    uint32_t bytes_to_reserve = interp.read_code_at(interp.curr_thread().pc++);
    interp.curr_thread().stk.reserve(bytes_to_reserve / 4);
}
register_instruction reserve_instr(0x11000000, 0xFF000000, reserve_handler);

void unreserve_handler(cscript& interp, uint32_t opcode)
{
    (void)opcode;

    uint32_t bytes_to_unres = interp.read_code_at(interp.curr_thread().pc++);
    interp.curr_thread().stk.unreserve(bytes_to_unres / 4);
}
register_instruction unreserve_instr(0x10000000, 0xFF000000, unreserve_handler);

void push_handler(cscript& interp, uint32_t opcode)
{
    uint16_t dest_type = opcode & 0xFFFF;
    uint32_t resulting_value = 0;
    variable& var = interp.curr_thread().scratch.top(0);

    if (dest_type != 0)
    {
        throw exception("push: cast not yet implemented");
    }

    var.value = resulting_value;
    interp.curr_thread().stk.push(resulting_value);
}
register_instruction push_instr(0x0E000000, 0xFF000000, push_handler);

}}
