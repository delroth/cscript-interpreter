#include "../cscript.hh"
#include "../exception.hh"
#include "../instruction-register.hh"

namespace cscript { namespace instruction {

void call_handler(cscript& interp, uint32_t opcode)
{
    (void)opcode;

    uint32_t target = interp.read_code_at(interp.curr_thread().pc++);
    if (target == 0xFFFFFFFF)
        throw exception("call: syscalls are not yet supported");
    else if (target % 4 != 0)
        throw exception("misaligned call target");

    interp.curr_thread().stk.push_frame(interp.curr_thread().pc);
    interp.curr_thread().pc = target / 4;
}
register_instruction call_instr(0x05000000, 0xFF000000, call_handler);

}}
