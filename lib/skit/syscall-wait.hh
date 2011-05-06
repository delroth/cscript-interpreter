#ifndef __SKIT_SYSCALL_WAIT_HH_
# define __SKIT_SYSCALL_WAIT_HH_

# include "../cscript.hh"

namespace cscript { namespace skit { namespace syscalls {

const uint16_t SKIT_WAIT_ID = 0x7A;
const uint16_t SKIT_WAIT2_ID = 0x7B;
void skit_wait(cscript& script, const std::vector<uint32_t>& args);

}}}

#endif
