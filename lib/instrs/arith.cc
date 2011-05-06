#include "../cscript.hh"
#include "../instruction-register.hh"
#include "../type.hh"
#include "../utils.hh"
#include "../variable.hh"

enum class arith_op
{
    PLUS,
    MINUS,
    TIMES,
};

namespace cscript { namespace instruction {

template <typename T>
T apply_op(arith_op op, T first_val, T second_val)
{
    switch (op)
    {
    case arith_op::PLUS:
        return (first_val + second_val);
    case arith_op::MINUS:
        return (first_val - second_val);
    case arith_op::TIMES:
        return (first_val * second_val);
    default:
        throw exception("unknown arithmetic operator used");
    }
}

void generic_arith_handler(cscript& interp, arith_op op)
{
    interp.curr_thread().scratch.pop();
    variable& first = interp.curr_thread().scratch.top(1);
    variable& second = interp.curr_thread().scratch.top(0);

    if (type::trivially_integer(first.type))
    {
        uint32_t first_val = first.value.u32;
        uint32_t second_val = second.cast_to(first.type);

        if (first.type & type::POINTER)
            second_val *= first.pointed_size;
        else if (first.type & type::POINTER2)
            second_val *= 4;

        first.value.u32 = apply_op<uint32_t>(op, first_val, second_val);
    }
    else
    {
        float first_val = utils::float_from_u32(first.value.u32);
        float second_val = utils::float_from_u32(second.cast_to(first.type));
        first.value.f32 = apply_op<float>(op, first_val, second_val);
    }

    first.write_value_to_addr(interp);
}

#define ARITH_HANDLER(Opcode, Oper) \
    void Oper##_##Opcode##_handler(cscript& interp, uint32_t opcode) \
    { \
        (void)opcode; \
        generic_arith_handler(interp, arith_op::Oper); \
    } \
    \
    register_instruction Oper##_##Opcode##_instr(Opcode, 0xFFFF0000, \
                                                 Oper##_##Opcode##_handler);

ARITH_HANDLER(0x010A0000, PLUS);
ARITH_HANDLER(0x011C0000, TIMES);
ARITH_HANDLER(0x011F0000, PLUS);
ARITH_HANDLER(0x01200000, MINUS);

}}
