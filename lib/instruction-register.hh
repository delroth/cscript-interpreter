#ifndef __INSTRUCTION_REGISTER_HH_
# define __INSTRUCTION_REGISTER_HH_

# include "instruction-dispatcher.hh"
# include "instruction-handler.hh"

# include <cstdint>

namespace cscript { namespace instruction {

/**
 * A structure which is used to register instruction handlers to the singleton
 * instruction dispatcher.
 *
 * Just statically create register_instruction instances and the object
 * constructor will handle the registration.
 */
struct register_instruction
{
    /**
     * Registers a handler for instructions where instr & mask == value.
     */
    register_instruction(uint32_t value, uint32_t mask, handler h)
    {
        dispatcher::get().register_handler(value, mask, h);
    }
};

}}

#endif
