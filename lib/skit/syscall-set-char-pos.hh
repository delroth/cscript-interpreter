#ifndef __SKIT_SYSCALL_SET_CHAR_POS_HH_
# define __SKIT_SYSCALL_SET_CHAR_POS_HH_

# include "../skit-cscript.hh"

namespace cscript { namespace skit { namespace syscalls {

const uint16_t SKIT_SET_CHAR_POS_ID = 0x68;
void skit_set_char_pos(skit_cscript& script,
                       const std::vector<uint32_t>& args);

}}}

#endif
