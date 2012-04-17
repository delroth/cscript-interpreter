#ifndef __TOS2_SCRIPT_SYSCALLS_HH_
# define __TOS2_SCRIPT_SYSCALLS_HH_

# include "../cscript.hh"

namespace cscript { namespace tos2_skit {

bool execute_syscall(cscript& script, uint16_t syscall,
                     const std::vector<uint32_t>& args);

}}

#endif
