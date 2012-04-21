#include "../address.hh"
#include "../cscript.hh"
#include "../instruction-register.hh"
#include "../type.hh"
#include "../variable.hh"

namespace cscript { namespace instruction {

void idx_handler(cscript& interp, uint32_t opcode)
{
    (void)opcode;

    variable& idx = interp.curr_thread().scratch.top(1);
    variable& arr = interp.curr_thread().scratch.top(2);
    interp.curr_thread().scratch.pop();

    if (arr.type & type::POINTER)
    {
        uint32_t off = idx.value.u32 * arr.pointed_size;
        if (address::is_stack_addr(arr.value.u32))
        {
            if (off % 4 != 0)
                throw exception("indexing stack with a non aligned offset");
            off /= 4;
        }

        arr.type &= 0xF;
        arr.address = arr.value.u32 + off;
        arr.value.u32 = arr.read_value_from_addr(interp);
    }
    else if (arr.type & type::POINTER2)
    {
        throw exception("IDX: not yet implemented for POINTER2");
    }
    else
    {
        throw exception("IDX: indexing a non pointer type");
    }
}

register_instruction idx_instr(0x01260000, 0xFFFF0000, idx_handler);

void rawidx_handler(cscript& interp, uint32_t opcode)
{
    uint32_t arg = interp.read_code_at(interp.curr_thread().pc++);
    uint16_t idx = arg & 0xFFFF;
    uint16_t elem_size = arg >> 16;
    uint8_t elem_type = opcode & 0xFF;

    variable& var = interp.curr_thread().scratch.top(1);

    if (address::is_stack_addr(var.address))
    {
        if (idx % 4 != 0)
            throw exception("rawidx on stack non aligned");
        idx /= 4;
    }

    var.address += idx;
    var.type = (var.type & 0xFF00) | elem_type;
    var.pointed_size = elem_size;
    var.value.u32 = var.read_value_from_addr(interp);
}

register_instruction rawidx_instr(0x012A0000, 0xFFFF0000, rawidx_handler);

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
}

register_instruction get_field_instr(0x012B0000, 0xFFFF0000, get_field_handler);

}}
