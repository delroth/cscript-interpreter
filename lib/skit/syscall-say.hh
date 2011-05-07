#ifndef __SKIT_SYSCALL_SAY_HH_
# define __SKIT_SYSCALL_SAY_HH_

# include "../skit-cscript.hh"

namespace cscript { namespace skit { namespace syscalls {

const uint16_t SKIT_SAY_ID = 0x76;
void skit_say(skit_cscript& script, const std::vector<uint32_t>& args);

}}}

#endif
