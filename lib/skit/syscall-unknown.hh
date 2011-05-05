#ifndef __SKIT_SYSCALL_UNKNOWN_HH_
# define __SKIT_SYSCALL_UNKNOWN_HH_

# include "../cscript.hh"

namespace cscript { namespace skit { namespace syscalls {

const uint16_t SKIT_UNKNOWN_ID = 0x64;
void skit_unknown(cscript& script);

const uint16_t SKIT_UNKNOWN2_ID = 0x6D;
void skit_unknown2(cscript& script);

}}}

#endif
