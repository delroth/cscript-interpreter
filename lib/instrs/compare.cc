#include "../cscript.hh"
#include "../instruction-register.hh"
#include "../type.hh"
#include "../utils.hh"
#include "../variable.hh"

#include <set>

enum class compare_op
{
    LE
};

namespace cscript { namespace instruction {

static const std::set<uint8_t> uint_types = {
    type::UCHAR,
    type::UHALF,
    type::UWORD,
    type::ADDR
};

template <typename T>
bool apply_op(compare_op op, T first_val, T second_val)
{
    switch (op)
    {
    case compare_op::LE:
        return (first_val <= second_val);
    default:
        return false;
    }
}

void generic_compare_handler(cscript& interp, compare_op op)
{
    (void)op;

    interp.curr_thread().scratch.pop();
    variable& first = interp.curr_thread().scratch.top(1);
    variable& second = interp.curr_thread().scratch.top(0);

    bool first_is_uint = false;
    if ((first.type & type::POINTER) || (first.type & type::POINTER2))
        first_is_uint = true;
    else if (uint_types.find(first.type) != uint_types.end())
        first_is_uint = true;

    bool first_is_int = (first.type != type::FLOAT);

    bool result;
    if (first_is_uint)
    {
        uint32_t first_val = first.value.u32;
        uint32_t second_val = second.cast_to(first.type);
        result = apply_op<uint32_t>(op, first_val, second_val);
    }
    else if (first_is_int)
    {
        int32_t first_val = first.value.u32;
        int32_t second_val = second.cast_to(first.type);
        result = apply_op<int32_t>(op, first_val, second_val);
    }
    else
    {
        float first_val = utils::float_from_u32(first.value.u32);
        float second_val = utils::float_from_u32(second.cast_to(first.type));
        result = apply_op<float>(op, first_val, second_val);
    }

    first.value.u32 = result;
    first.type = type::IMMEDIATE | type::SWORD;
    first.address = 0;
    first.pointed_size = 4;
}

void le_handler(cscript& interp, uint32_t opcode)
{
    (void)opcode;
    generic_compare_handler(interp, compare_op::LE);
}

register_instruction le_instr(0x01160000, 0xFFFF0000, le_handler);

}}
