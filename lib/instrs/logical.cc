#include "../cscript.hh"
#include "../instruction-register.hh"
#include "../type.hh"
#include "../variable.hh"

#include <functional>

namespace cscript { namespace instruction {

void generic_logical_handler(cscript& interp,
                             std::function<bool(bool, bool)> f)
{
    interp.curr_thread().scratch.pop();
    variable& first = interp.curr_thread().scratch.top(1);
    variable& second = interp.curr_thread().scratch.top(0);

    first.value.u32 = f(first.boolean_value(), second.boolean_value());
    first.type = type::IMMEDIATE | type::SWORD;
    first.address = 0;
    first.pointed_size = 4;
}

#define LOGICAL_HANDLER(Opcode, Oper, Func) \
    void Oper##_handler(cscript& interp, uint32_t opcode) \
    { \
        (void)opcode; \
        generic_logical_handler(interp, Func<bool>()); \
    } \
    \
    register_instruction Oper##_instr(Opcode, 0xFFFF0000, Oper##_handler)

LOGICAL_HANDLER(0x011B0000, or, std::logical_or);

}}
