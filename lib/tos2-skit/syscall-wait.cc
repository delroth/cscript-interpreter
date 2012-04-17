#include "../type.hh"
#include "syscall-wait.hh"

namespace cscript { namespace tos2_skit { namespace syscalls {

void skit_wait_start(tos2_skit_cscript& script, const std::vector<uint32_t>& args)
{
    (void)args;

    script.curr_thread().st |= thread_state::WAIT_EVENT;
    script.backend().wait_start(&script.curr_thread().event_triggered);

    variable& v = script.curr_thread().scratch.top(0);
    v.value.u32 = 0;
    v.address = 0;
    v.type = type::IMMEDIATE | type::SWORD;
    script.curr_thread().scratch.push();
}

void skit_wait(tos2_skit_cscript& script, const std::vector<uint32_t>& args)
{
    (void)args;

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
