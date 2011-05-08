#ifndef __SKIT_SYSCALL_INIT_CHAR_HH_
# define __SKIT_SYSCALL_INIT_CHAR_HH_

# include "../skit-cscript.hh"

namespace cscript { namespace skit { namespace syscalls {

const uint16_t SKIT_INIT_CHAR_ID = 0x64;
void skit_init_char(skit_cscript& script, const std::vector<uint32_t>& args);

}}}

#endif
