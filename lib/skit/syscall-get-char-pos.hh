#ifndef __SKIT_SYSCALL_GET_CHAR_POS_HH_
# define __SKIT_SYSCALL_GET_CHAR_POS_HH_

# include "../skit-cscript.hh"

namespace cscript { namespace skit { namespace syscalls {

const uint16_t SKIT_GET_CHAR_POS_ID = 0x67;
void skit_get_char_pos(skit_cscript& script,
                       const std::vector<uint32_t>& args);

}}}

#endif
