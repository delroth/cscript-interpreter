#ifndef __TOS2_SCRIPT_SYSCALL_SAY_HH_
# define __TOS2_SCRIPT_SYSCALL_SAY_HH_

# include "../tos2-skit-cscript.hh"

namespace cscript { namespace tos2_skit { namespace syscalls {

const uint16_t SKIT_SAY_ID = 0x76;
void skit_say(tos2_skit_cscript& script, const std::vector<uint32_t>& args);

}}}

#endif
