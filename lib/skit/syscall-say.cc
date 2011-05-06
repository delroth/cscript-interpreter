#include "../address.hh"
#include "../type.hh"
#include "syscall-say.hh"

#include <iostream>
#include <string>

namespace cscript { namespace skit { namespace syscalls {

void skit_say(cscript& script, const std::vector<uint32_t>& args)
{
    std::string name = address::get_ptr(script, args[0]);
    std::string msg = address::get_ptr(script, args[1]);

    std::cerr << "[log] " << name << " says: " << msg << std::endl;

    // Return value.
    variable& v = script.curr_thread().scratch.top(0);

    v.value.u32 = 0;
    v.address = 0;
    v.type = type::IMMEDIATE | type::SWORD;

    script.curr_thread().scratch.push();
}

}}}
