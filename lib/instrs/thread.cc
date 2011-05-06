#include "../cscript.hh"
#include "../instruction-register.hh"
#include "../thread-context.hh"
#include "../type.hh"
#include "../variable.hh"

namespace cscript { namespace instruction {

void spawn_handler(cscript& interp, uint32_t opcode)
{
    uint8_t nargs = (opcode & 0x00FF0000) >> 16;
    uint32_t target = interp.read_code_at(interp.curr_thread().pc++);

    uint16_t tid;
    for (tid = 0; tid < MAX_THREADS; ++tid)
        if (!(interp.thread(tid).st & thread_state::RUNNABLE))
            break;

    if (tid == MAX_THREADS)
        throw exception("unable to find a free thread id");

    thread_context& tc = interp.thread(tid);
    tc.pc = target / 4;
    tc.st = thread_state::RUNNABLE;
    tc.frames_to_wait = 0;
    tc.event_triggered = false;
    tc.stk = stack();
    tc.scratch = scratchpad();

    uint32_t arg_pos = interp.curr_thread().stk.top() + nargs - 1;
    for (uint8_t i = 0; i < nargs; ++i)
        tc.stk.push(interp.curr_thread().stk.at(arg_pos--));

    tc.stk.push_frame(0xDEADBEAF);

    variable& v = interp.curr_thread().scratch.top(0);
    v.value.u32 = tid;
    v.address = 0;
    v.pointed_size = 4;
    v.type = type::IMMEDIATE | type::UWORD;
    interp.curr_thread().scratch.push();
}

register_instruction spawn_instr(0x13000000, 0xFF000000, spawn_handler);

}}
