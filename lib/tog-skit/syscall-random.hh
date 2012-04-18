#ifndef __TOG_SKIT_SYSCALL_RANDOM_HH_
# define __TOG_SKIT_SYSCALL_RANDOM_HH_

# include "../tog-skit-cscript.hh"

namespace cscript { namespace tog_skit { namespace syscalls {

const uint16_t SKIT_RANDOM = 0x0021;
void skit_random(tog_skit_cscript& script, const std::vector<uint32_t>& args);

}}}

#endif
