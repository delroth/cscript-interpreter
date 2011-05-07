#ifndef __SKIT_SYSCALL_INIT_HH_
# define __SKIT_SYSCALL_INIT_HH_

# include "../skit-cscript.hh"

namespace cscript { namespace skit { namespace syscalls {

const uint16_t SKIT_INIT_ID = 0x79;
void skit_init(skit_cscript& script, const std::vector<uint32_t>& args);

}}}

#endif
