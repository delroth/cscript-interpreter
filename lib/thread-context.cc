#include "thread-context.hh"

namespace cscript {

bool thread_context::yielding()
{
    if (st & thread_state::WAIT_FRAMES)
    {
        if (frames_to_wait > 0)
        {
            frames_to_wait -= 1;
            return true;
        }
        else
        {
            st &= ~thread_state::WAIT_FRAMES;
            return false;
        }
    }
    else if (st & thread_state::WAIT_EVENT)
    {
        if (!event_triggered)
        {
            return true;
        }
        else
        {
            st &= ~thread_state::WAIT_EVENT;
            event_triggered = false;
            return true;
        }
    }
    else
        return false;
}

}
