#ifndef __VARIABLE_HH_
# define __VARIABLE_HH_

# include <cstdint>

namespace cscript {

/**
 * Represents a variable used to store a computed value in the interpreter.
 *
 * See also the scratchpad class which is the place where variables are stored.
 */
struct variable
{
    /**
     * The variable value.
     */
    uint32_t value;

    /**
     * If the variable is not an immediate value but is instead referencing
     * memory, the address the variable is referencing.
     */
    uint32_t address;

    /**
     * The type of the variable. See type.h.
     */
    uint16_t type;

    /**
     * In case of a pointer variable, the size of the pointed type. Useful for
     * indexing, for example.
     */
    uint16_t pointed_size;
};

}

#endif
