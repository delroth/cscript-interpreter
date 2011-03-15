#ifndef __THREAD_CONTEXT_HH_
# define __THREAD_CONTEXT_HH_

# include "scratchpad.hh"
# include "stack.hh"

# include <cstdint>

namespace cscript {

const uint32_t MAX_THREADS = 0x20;

struct thread_context
{
    /**
     * The program counter, aka. where is the next instruction.
     */
    uint32_t pc;

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

}

#endif