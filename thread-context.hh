#ifndef __THREAD_CONTEXT_HH_
# define __THREAD_CONTEXT_HH_

# include <cstdint>

namespace cscript {

const uint32_t MAX_THREADS = 0x20;

struct thread_context
{
    uint32_t pc;
};

}

#endif
