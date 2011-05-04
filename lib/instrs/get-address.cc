#include "../cscript.hh"
#include "../instruction-register.hh"
#include "../type.hh"
#include "../variable.hh"

namespace cscript { namespace instruction {

void get_addr_handler(cscript& interp, uint32_t opcode)
{
    (void)opcode;

    variable& var = interp.curr_thread().scratch.top(1);

    if ((var.type & type::POINTER) || (var.type & type::POINTER2))
    {
        throw exception("unable to get the address of a pointer to a pointer");
    }

    var.value.u32 = var.address;
    var.address = 0;
    var.type = type::IMMEDIATE | type::POINTER | (var.type & 0xF);
}

register_instruction get_addr_instr(0x01280000, 0xFFFF0000, get_addr_handler);

}}
