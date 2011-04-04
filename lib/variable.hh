#ifndef __VARIABLE_HH_
# define __VARIABLE_HH_

# include <cstdint>
# include <iomanip>

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

/*
 * Dumping function.
 */
template <typename T>
T& operator<<(T& str, const variable& v)
{
    std::ios_base::fmtflags fmt = str.flags();

    str << "<v=0x" << std::hex << std::setfill('0') << std::setw(8)
        << v.value.u32;
    str << " a=0x" << std::hex << std::setfill('0') << std::setw(8)
        << v.address;
    str << " t=0x" << std::hex << std::setfill('0') << std::setw(4) << v.type;
    str << " ps=0x" << std::hex << std::setfill('0') << std::setw(4)
        << v.pointed_size;
    str << ">";

    str.flags(fmt);
    return str;

}

}

#endif
