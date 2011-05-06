#ifndef __SKIT_SYSCALL_UNKNOWN_HH_
# define __SKIT_SYSCALL_UNKNOWN_HH_

# include "../cscript.hh"

namespace cscript { namespace skit { namespace syscalls {

const uint16_t SKIT_UNKNOWN_ID = 0x64;
void skit_unknown(cscript& script, const std::vector<uint32_t>& args);

const uint16_t SKIT_UNKNOWN2_ID = 0x6D;
void skit_unknown2(cscript& script, const std::vector<uint32_t>& args);

const uint16_t SKIT_UNKNOWN3_ID = 0x73;
void skit_unknown3(cscript& script, const std::vector<uint32_t>& args);

const uint16_t SKIT_UNKNOWN4_ID = 0x6B;
void skit_unknown4(cscript& script, const std::vector<uint32_t>& args);

}}}

#endif
