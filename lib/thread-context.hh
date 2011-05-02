#ifndef __THREAD_CONTEXT_HH_
# define __THREAD_CONTEXT_HH_

# include "scratchpad.hh"
# include "stack.hh"

# include <cstdint>

namespace cscript {

const uint32_t MAX_THREADS = 0x20;

/**
 * Used to specify in which state the thread is currently.
 */
enum thread_state
{
    NOT_RUNNING = 0x0,
    RUNNABLE = 0x1,
    WAIT_FRAMES = 0x4,
    WAIT_EVENT = 0x8,
    RUNNING = 0x10
};

struct thread_context
{
    thread_context() : pc(0), st(thread_state::NOT_RUNNING), frames_to_wait(0),
                       event_triggered(false), stk(), scratch()
    {
    }

    /**
     * The program counter, aka. where is the next instruction.
     */
    uint32_t pc;

    /**
     * The current state of the thread: whereas it can be run or is running,
     * for example.
     */
    thread_state st;

    /**
     * For how much frames are we still waiting.
     */
    uint32_t frames_to_wait;

    /**
     * Has the event we are waiting for been triggered yet?
     */
    bool event_triggered;

    /**
     * The stack, which contains function arguments as well as return address
     * and the old stack frame base.
     */
    stack stk;

    /**
     * The scratchpad, temporary storage zone for variables used in
     * computations, or stored as return value of a function.
     */
    scratchpad scratch;
};

/*
 * Dumping function.
 */
template <typename T>
T& operator<<(T& str, const thread_context& t)
{
    std::ios_base::fmtflags fmt = str.flags();

    str << "THREAD CONTEXT" << std::endl;
    str << "==============" << std::endl << std::endl;

    str << "PC = 0x";
    str << std::hex << std::setfill('0') << std::setw(8);
    str << t.pc << std::endl;
    str << t.stk << std::endl;
    str << t.scratch << std::endl;

    str.flags(fmt);
    return str;
}

}

#endif
