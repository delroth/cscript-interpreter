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
    MOD,
    DIV,
    AND,
    OR,
    SHR,
};

namespace cscript { namespace instruction {

template <typename T>
T apply_op_gen(arith_op op, T first_val, T second_val)
{
    switch (op)
    {
    case arith_op::PLUS:
        return (first_val + second_val);
    case arith_op::MINUS:
        return (first_val - second_val);
    case arith_op::TIMES:
        return (first_val * second_val);
    case arith_op::DIV:
        if (second_val == 0)
            throw exception("division by zero");
        return (first_val / second_val);
    default:
        throw exception("unknown arithmetic operator used");
    }
}

uint32_t apply_op_int(arith_op op, uint32_t first_val, uint32_t second_val)
{
    switch (op)
    {
    case arith_op::MOD:
        return (first_val % second_val);
    case arith_op::AND:
        return (first_val & second_val);
    case arith_op::OR:
        return (first_val | second_val);
    case arith_op::SHR:
        return (first_val >> second_val);
    default:
        return apply_op_gen<uint32_t>(op, first_val, second_val);
    }
}

float apply_op_float(arith_op op, float first_val, float second_val)
{
    return apply_op_gen<float>(op, first_val, second_val);
}

template <bool AllowFloats, bool UpdateMem>
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

        first.value.u32 = apply_op_int(op, first_val, second_val);
    }
    else if (AllowFloats)
    {
        float first_val = utils::float_from_u32(first.value.u32);
        float second_val = utils::float_from_u32(second.cast_to(first.type));
        first.value.f32 = apply_op_float(op, first_val, second_val);
    }
    else
    {
        throw exception("unexpected type in arithmetic operation");
    }

    if (UpdateMem)
        first.write_value_to_addr(interp);
}

#define ARITH_HANDLER(Opcode, Oper, AllowFloats, UpdateMem) \
    void Oper##_##Opcode##_handler(cscript& interp, uint32_t opcode) \
    { \
        (void)opcode; \
        generic_arith_handler<AllowFloats, UpdateMem>(interp, arith_op::Oper); \
    } \
    \
    register_instruction Oper##_##Opcode##_instr(Opcode, 0xFFFF0000, \
                                                 Oper##_##Opcode##_handler);

ARITH_HANDLER(0x010A0000, PLUS, true, true);
ARITH_HANDLER(0x010B0000, MINUS, true, true);
ARITH_HANDLER(0x011A0000, AND, false, false);
ARITH_HANDLER(0x011C0000, TIMES, true, false);
ARITH_HANDLER(0x011D0000, DIV, true, false);
ARITH_HANDLER(0x011E0000, MOD, false, false);
ARITH_HANDLER(0x011F0000, PLUS, true, false);
ARITH_HANDLER(0x01200000, MINUS, true, false);
ARITH_HANDLER(0x01210000, AND, false, false);
ARITH_HANDLER(0x01220000, OR, false, false);
ARITH_HANDLER(0x01250000, SHR, false, false);

}}
