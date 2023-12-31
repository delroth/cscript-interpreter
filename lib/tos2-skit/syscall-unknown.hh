#ifndef __TOS2_SCRIPT_SYSCALL_UNKNOWN_HH_
# define __TOS2_SCRIPT_SYSCALL_UNKNOWN_HH_

# include "../tos2-skit-cscript.hh"

namespace cscript { namespace tos2_skit { namespace syscalls {

#define UNKNOWN_DECL(n, id) \
    const uint16_t SKIT_UNKNOWN##n##_ID = id; \
    void skit_unknown##n(tos2_skit_cscript& script, \
                         const std::vector<uint32_t>& args);

UNKNOWN_DECL(1, 0x65)
UNKNOWN_DECL(2, 0x6B)
UNKNOWN_DECL(3, 0x6C)
UNKNOWN_DECL(4, 0x6D)
UNKNOWN_DECL(5, 0x6E)
UNKNOWN_DECL(6, 0x6F)
UNKNOWN_DECL(7, 0x70)
UNKNOWN_DECL(8, 0x72)
UNKNOWN_DECL(9, 0x73)
UNKNOWN_DECL(10, 0x77)
UNKNOWN_DECL(11, 0x7e)
UNKNOWN_DECL(12, 0x7f)

const uint16_t SKIT_SETSOMETHING_ID = 0x68;
void skit_setsomething(tos2_skit_cscript& script,
                       const std::vector<uint32_t>& args);

}}}

#endif
