#ifndef __TOS2_SCRIPT_SYSCALL_INIT_HH_
# define __TOS2_SCRIPT_SYSCALL_INIT_HH_

# include "../tos2-skit-cscript.hh"

namespace cscript { namespace tos2_skit { namespace syscalls {

const uint16_t SKIT_INIT_ID = 0x79;
void skit_init(tos2_skit_cscript& script, const std::vector<uint32_t>& args);

}}}

#endif
