#include "syscall-unknown.hh"

namespace cscript { namespace tog_skit { namespace syscalls {

#define UNKNOWN_HANDLER(n) \
    int32_t skit_unknown##n(tog_skit_cscript& script, \
                         const std::vector<uint32_t>& args) \
    { \
        (void)script; \
        (void)args; \
        return 0; \
    }

UNKNOWN_HANDLER(1)
UNKNOWN_HANDLER(2)
UNKNOWN_HANDLER(3)

}}}
