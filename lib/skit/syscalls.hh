#ifndef __SKIT_SYSCALLS_HH_
# define __SKIT_SYSCALLS_HH_

# include "../cscript.hh"

namespace cscript { namespace skit {

bool execute_syscall(cscript& script, uint16_t syscall,
                     const std::vector<uint32_t>& args);

}}

#endif
