#include "../address.hh"
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

void get_field_handler(cscript& interp, uint32_t opcode)
{
    uint8_t dest_type = opcode & 0xFF;

    uint32_t argument = interp.read_code_at(interp.curr_thread().pc++);
    uint16_t off = argument & 0xFFFF;
    uint16_t pointed_size = argument >> 16;

    variable& v = interp.curr_thread().scratch.top(1);

    if (!(v.type & type::POINTER))
        throw exception("getting field on a non-pointer type");

    v.address = address::offset(address::uword_at(interp, v.address), off);
    v.pointed_size = pointed_size;
    v.type = dest_type;
    v.value.u32 = v.read_value_from_addr(interp);

    if (v.type & type::POINTER)
    {
        if (v.value.u32 != 0 && v.value.u32 < interp.data_size())
            v.value.u32 = address::make_data_addr(v.value.u32);
    }
    else if (v.type & type::POINTER3)
        throw exception("getting a pointer3 field is not yet supported");

    std::cerr << interp.curr_thread();
}

register_instruction get_field_instr(0x012B0000, 0xFFFF0000, get_field_handler);

}}
