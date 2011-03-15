#include "../cscript.hh"
#include "../instruction-register.hh"

namespace cscript { namespace instruction {

void exit_handler(cscript& interp, uint32_t opcode)
{
    (void)opcode;
    interp.exit();
}
register_instruction exit_instr(0x07000000, 0xFF000000, exit_handler);

}}
