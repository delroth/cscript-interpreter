#ifndef __TOG_SKIT_SYSCALL_UNKNOWN_HH_
# define __TOG_SKIT_SYSCALL_UNKNOWN_HH_

#include "../tog-skit-cscript.hh"

namespace cscript { namespace tog_skit { namespace syscalls {

#define UNKNOWN_DECL(n, id) \
    const uint16_t SKIT_UNKNOWN##n##_ID = id; \
    int32_t skit_unknown##n(tog_skit_cscript& script, \
                            const std::vector<uint32_t>& args);

UNKNOWN_DECL(1, 0x0317)
UNKNOWN_DECL(2, 0x0204)
UNKNOWN_DECL(3, 0x0206)
UNKNOWN_DECL(4, 0x0212)
UNKNOWN_DECL(5, 0x020a)
UNKNOWN_DECL(6, 0x0213)
UNKNOWN_DECL(7, 0x0202)
UNKNOWN_DECL(8, 0x020d)
UNKNOWN_DECL(9, 0x020f)
UNKNOWN_DECL(10, 0x0207)
UNKNOWN_DECL(11, 0x020e)
UNKNOWN_DECL(12, 0x0203)

}}}

#endif
