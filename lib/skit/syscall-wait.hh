#ifndef __SKIT_SYSCALL_WAIT_HH_
# define __SKIT_SYSCALL_WAIT_HH_

# include "../cscript.hh"

namespace cscript { namespace skit { namespace syscalls {

const uint16_t SKIT_WAIT_ID = 0x7A;
const uint16_t SKIT_WAIT2_ID = 0x7B;
const uint16_t SKIT_WAIT3_ID = 0x69;
const uint16_t SKIT_WAIT4_ID = 0x7C;
const uint16_t SKIT_WAIT5_ID = 0x6A;
void skit_wait(cscript& script, const std::vector<uint32_t>& args);

}}}

#endif
