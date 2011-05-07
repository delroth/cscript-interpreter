#include "../address.hh"
#include "../type.hh"
#include "../utils.hh"
#include "syscall-unknown.hh"

#include <map>

namespace cscript { namespace skit { namespace syscalls {

#define UNKNOWN_HANDLER(n) \
    void skit_unknown##n(cscript& script, const std::vector<uint32_t>& args) \
    { \
        (void)args; \
     \
        variable& v = script.curr_thread().scratch.top(0); \
     \
        v.value.u32 = 0; \
        v.address = 0; \
        v.type = type::IMMEDIATE | type::SWORD; \
     \
        script.curr_thread().scratch.push(); \
    }

UNKNOWN_HANDLER(1)
UNKNOWN_HANDLER(2)
UNKNOWN_HANDLER(3)
UNKNOWN_HANDLER(4)
UNKNOWN_HANDLER(5)
UNKNOWN_HANDLER(6)
UNKNOWN_HANDLER(7)
UNKNOWN_HANDLER(8)
UNKNOWN_HANDLER(9)
UNKNOWN_HANDLER(10)
UNKNOWN_HANDLER(11)
UNKNOWN_HANDLER(12)

struct something
{
    float x, y;
    uint32_t something;
};

std::map<uint32_t, something> init_values;

void skit_initsomething(cscript& script, const std::vector<uint32_t>& args)
{
    uint32_t id = args[0];
    float x = utils::float_from_u32(args[2]);
    float y = utils::float_from_u32(args[3]);

    init_values[id] = { x, y, args[4] };

    variable& v = script.curr_thread().scratch.top(0);

    v.value.u32 = 0;
    v.address = 0;
    v.pointed_size = 4;
    v.type = type::IMMEDIATE | type::SWORD;

    script.curr_thread().scratch.push();
}

void skit_getsomething(cscript& script, const std::vector<uint32_t>& args)
{
    float* px = (float*)address::get_ptr(script, args[1]);
    float* py = (float*)address::get_ptr(script, args[2]);

    auto it = init_values.find(args[0]);
    if (it == init_values.end())
        throw exception("unable to find the float values");
    *px = it->second.x;
    *py = it->second.y;

    variable& v = script.curr_thread().scratch.top(0);

    v.value.u32 = 0;
    v.address = 0;
    v.pointed_size = 4;
    v.type = type::IMMEDIATE | type::SWORD;

    script.curr_thread().scratch.push();
}

void skit_setsomething(cscript& script, const std::vector<uint32_t>& args)
{
    uint32_t id = args[0];
    float x = utils::float_from_u32(args[1]);
    float y = utils::float_from_u32(args[2]);

    init_values[id].x = x;
    init_values[id].y = y;

    variable& v = script.curr_thread().scratch.top(0);

    v.value.u32 = 0;
    v.address = 0;
    v.pointed_size = 4;
    v.type = type::IMMEDIATE | type::SWORD;

    script.curr_thread().scratch.push();
}

}}}
