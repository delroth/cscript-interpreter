#include "../type.hh"
#include "syscall-unknown.hh"

namespace cscript { namespace skit { namespace syscalls {

#define UNKNOWN_HANDLER(n) \
    void skit_unknown##n(cscript& script, const std::vector<uint32_t>& args) \
    { \
        (void)args; \
     \
        variable& v = script.curr_thread().scratch.top(0); \
     \
        v.value.u32 = 0; \
        v.address = 0; \
        v.type = type::IMMEDIATE | type::SWORD; \
     \
        script.curr_thread().scratch.push(); \
    }

UNKNOWN_HANDLER(1)
UNKNOWN_HANDLER(2)
UNKNOWN_HANDLER(3)
UNKNOWN_HANDLER(4)
UNKNOWN_HANDLER(5)
UNKNOWN_HANDLER(6)

}}}
