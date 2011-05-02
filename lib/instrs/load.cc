#include "../address.hh"
#include "../cscript.hh"
#include "../instruction-register.hh"
#include "../type.hh"

namespace cscript { namespace instruction {

namespace {

void load_immediate(cscript& interp, uint32_t value, uint8_t val_type)
{
    variable& var = interp.curr_thread().scratch.top(0);
    var.value.u32 = value;
    var.address = 0;
    var.type = type::IMMEDIATE | val_type;
    var.pointed_size = 0;
    interp.curr_thread().scratch.push();
}

}

void load_schar_handler(cscript& interp, uint32_t opcode)
{
    load_immediate(interp, (int8_t)(opcode & 0xFF), type::SCHAR);
}
register_instruction load_schar_instr(0x02030000, 0xFFFF0000,
                                      load_schar_handler);

void load_sword_handler(cscript& interp, uint32_t opcode)
{
    (void)opcode;

    uint32_t value = interp.read_code_at(interp.curr_thread().pc++);
    load_immediate(interp, value, type::SWORD);
}
register_instruction load_sword_instr(0x02070000, 0xFFFF0000,
                                      load_sword_handler);

void load_float_handler(cscript& interp, uint32_t opcode)
{
    (void)opcode;

    uint32_t value = interp.read_code_at(interp.curr_thread().pc++);
    load_immediate(interp, value, type::FLOAT);
}
register_instruction load_float_instr(0x02080000, 0xFFFF0000,
                                      load_float_handler);

void load_data_addr_handler(cscript& interp, uint32_t opcode)
{
    (void)opcode;

    uint32_t addr = interp.read_code_at(interp.curr_thread().pc++);
    load_immediate(interp, address::make_data_addr(addr),
                   type::POINTER | type::UCHAR);
}

register_instruction load_data_addr_instr(0x02820000, 0xFFFF0000,
                                          load_data_addr_handler);
register_instruction load_data_addr_instr2(0x02840000, 0xFFFF0000,
                                           load_data_addr_handler);

}}
