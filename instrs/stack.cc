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

}}
