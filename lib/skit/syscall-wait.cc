#include "../type.hh"
#include "syscall-wait.hh"

namespace cscript { namespace skit { namespace syscalls {

void skit_wait(cscript& script)
{
    // There is nothing to wait for currently. Just set to waiting state and
    // set the event flag directly.
    script.curr_thread().st |= thread_state::WAIT_EVENT;
    script.curr_thread().event_triggered = true;

    // Return value.
    variable& v = script.curr_thread().scratch.top(0);

    v.value.u32 = 0;
    v.address = 0;
    v.type = type::IMMEDIATE | type::SWORD;

    script.curr_thread().scratch.push();
}

}}}
