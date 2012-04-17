#ifndef __TOS2_SCRIPT_SYSCALL_GET_CHAR_POS_HH_
# define __TOS2_SCRIPT_SYSCALL_GET_CHAR_POS_HH_

# include "../tos2-skit-cscript.hh"

namespace cscript { namespace tos2_skit { namespace syscalls {

const uint16_t SKIT_GET_CHAR_POS_ID = 0x67;
void skit_get_char_pos(tos2_skit_cscript& script,
                       const std::vector<uint32_t>& args);

}}}

#endif
