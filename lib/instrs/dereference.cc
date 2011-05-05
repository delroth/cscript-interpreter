#include "../cscript.hh"
#include "../instruction-register.hh"
#include "../type.hh"
#include "../variable.hh"

namespace cscript { namespace instruction {

void deref_handler(cscript& interp, uint32_t opcode)
{
    (void)opcode;
    variable& v = interp.curr_thread().scratch.top(1);

    if (v.type & type::POINTER)
    {
        v.address = v.value.u32;
        v.type &= 0xF;
        v.value.u32 = v.read_value_from_addr(interp);
    }
    else if (v.type & type::POINTER2)
        throw exception("dereferencing pointer2 is not yet implemented");
    else
        throw exception("dereferencing a non pointer value");
}

register_instruction deref_instr(0x01270000, 0xFFFF0000, deref_handler);

}}
