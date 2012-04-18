#ifndef __TOG_SKIT_SYSCALL_STRINGS_HH_
# define __TOG_SKIT_SYSCALL_STRINGS_HH_

# include "../tog-skit-cscript.hh"

namespace cscript { namespace tog_skit { namespace syscalls {

const uint16_t SKIT_GET_STRING = 0x0039;
void skit_get_string(tog_skit_cscript& script,
                     const std::vector<uint32_t>& args);

}}}

#endif
