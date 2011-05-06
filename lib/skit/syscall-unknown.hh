#ifndef __SKIT_SYSCALL_UNKNOWN_HH_
# define __SKIT_SYSCALL_UNKNOWN_HH_

# include "../cscript.hh"

namespace cscript { namespace skit { namespace syscalls {

#define UNKNOWN_DECL(n, id) \
    const uint16_t SKIT_UNKNOWN##n##_ID = id; \
    void skit_unknown##n(cscript& script, const std::vector<uint32_t>& args);

UNKNOWN_DECL(1, 0x64)
UNKNOWN_DECL(2, 0x6B)
UNKNOWN_DECL(3, 0x6D)
UNKNOWN_DECL(4, 0x72)
UNKNOWN_DECL(5, 0x73)

}}}

#endif
