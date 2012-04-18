#include "syscall-random.hh"

#include <cstdlib>
#include <ctime>

namespace cscript { namespace tog_skit { namespace syscalls {

int32_t skit_random(tog_skit_cscript&, const std::vector<uint32_t>& args)
{
    static bool initialized = false;
    if (!initialized)
    {
        srand(time(NULL));
        initialized = true;
    }

    return args[0] ? rand() % args[0] : 0;
}

}}}
