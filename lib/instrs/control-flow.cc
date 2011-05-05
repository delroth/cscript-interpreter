#include "../cscript.hh"
#include "../exception.hh"
#include "../instruction-register.hh"
#include "../type.hh"

namespace cscript { namespace instruction {

void call_handler(cscript& interp, uint32_t opcode)
{
    (void)opcode;

    uint32_t target = interp.read_code_at(interp.curr_thread().pc++);
    if (target == 0xFFFFFFFF)
    {
        // TODO: Handle arguments?
        uint16_t syscall_id = opcode & 0xFFFF;
        interp.handle_syscall(syscall_id);
    }
    else if (target % 4 != 0)
        throw exception("misaligned call target");
    else
    {
        interp.curr_thread().stk.push_frame(interp.curr_thread().pc);
        interp.curr_thread().pc = target / 4;
    }
}

register_instruction call_instr(0x05000000, 0xFF000000, call_handler);

void ret_handler(cscript& interp, uint32_t opcode)
{
    interp.curr_thread().pc = interp.curr_thread().stk.pop_frame();

    uint16_t rettype = type::IMMEDIATE | ((opcode >> 16) & 0xFF);
    interp.curr_thread().scratch.top(0).type = rettype;
    interp.curr_thread().scratch.push();
}

register_instruction ret_instr(0x06000000, 0xFF000000, ret_handler);

void jump_handler(cscript& interp, uint32_t opcode)
{
    (void)opcode;

    uint32_t target = interp.read_code_at(interp.curr_thread().pc++);
    if (target % 4 != 0)
        throw exception("misaligned jump target");

    interp.curr_thread().pc = target / 4;
}

register_instruction jump_instr(0x08000000, 0xFF000000, jump_handler);

void jumpz_handler(cscript& interp, uint32_t opcode)
{
    (void)opcode;

    uint32_t target = interp.read_code_at(interp.curr_thread().pc++);
    if (target % 4 != 0)
        throw exception("misaligned jumpz target");

    variable& v = interp.curr_thread().scratch.top(0);
    if (!v.value.u32)
        interp.curr_thread().pc = target / 4;
}

register_instruction jumpz_instr(0x09000000, 0xFF000000, jumpz_handler);

}}
