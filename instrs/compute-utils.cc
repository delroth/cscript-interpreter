#include "../cscript.hh"
#include "../instruction-register.hh"

namespace cscript { namespace instruction {

void pop_handler(cscript& interp, uint32_t opcode)
{
    (void)opcode;
    interp.curr_thread().scratch.pop();
}
register_instruction pop_instr(0x01000000, 0xFFFF0000, pop_handler);

}}
