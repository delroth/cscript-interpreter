#include "../type.hh"
#include "syscall-random.hh"

#include <cstdlib>
#include <ctime>

namespace cscript { namespace tog_skit { namespace syscalls {

void skit_random(tog_skit_cscript& script, const std::vector<uint32_t>& args)
{
    static bool initialized = false;
    if (!initialized)
    {
        srand(time(NULL));
        initialized = true;
    }

    variable& v = script.curr_thread().scratch.top(0);
    v.value.u32 = args[0] ? rand() % args[0] : 0;
    v.address = 0;
    v.type = type::IMMEDIATE | type::SWORD;
    script.curr_thread().scratch.push();
}

}}}
