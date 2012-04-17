#ifndef __TOS2_SCRIPT_SYSCALL_INIT_CHAR_HH_
# define __TOS2_SCRIPT_SYSCALL_INIT_CHAR_HH_

# include "../tos2-skit-cscript.hh"

namespace cscript { namespace tos2_skit { namespace syscalls {

const uint16_t SKIT_INIT_CHAR_ID = 0x64;
void skit_init_char(tos2_skit_cscript& script, const std::vector<uint32_t>& args);

}}}

#endif
