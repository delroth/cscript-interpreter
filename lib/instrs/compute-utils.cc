#include "../cscript.hh"
#include "../instruction-register.hh"

namespace cscript { namespace instruction {

void popvar_handler(cscript& interp, uint32_t opcode)
{
    (void)opcode;
    interp.curr_thread().scratch.pop();
}
register_instruction popvar_instr(0x01000000, 0xFFFF0000, popvar_handler);

}}
