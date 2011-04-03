#ifndef __VARIABLE_HH_
# define __VARIABLE_HH_

# include <cstdint>

namespace cscript {

// Forward declaration
class cscript;

/**
 * Represents a variable used to store a computed value in the interpreter.
 *
 * See also the scratchpad class which is the place where variables are stored.
 */
struct variable
{
    /**
     * Constructor which initializes the variable to a 0 value/addr.
     */
    variable() : address(0), type(0), pointed_size(0)
    {
        value.u32 = 0;
    }

    /**
     * Converts the variable value to another type.
     */
    uint32_t cast_to(uint16_t type) const;

    /**
     * Reads the variable value from its address.
     */
    uint32_t read_value_from_addr(const cscript& interp) const;

    /**
     * Reciprocal of "read_value_from_addr": stores the current variable
     * value to its memory address.
     */
    void write_value_to_addr(cscript& interp) const;

    /**
     * The variable value.
     */
    union value_type
    {
        uint32_t u32;
        int32_t s32;
        float f32;
    } value;

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
