#ifndef __TOG_SKIT_BACKEND_HH_
# define __TOG_SKIT_BACKEND_HH_

# include <cstdint>

namespace cscript { namespace tog_skit {

/**
 * Backend of a Tales of Graces script, which exports methods used by the skit.
 */
class backend
{
public:
    /**
     * Returns the base pointer of the string table (.scs file).
     *
     * @return A pointer to the string table.
     */
    virtual char* get_stringtable_base() = 0;

    /**
     * Gets the offset of a string in the string table.
     *
     * @param idx The index of the string.
     * @return The offset from the start of the string table.
     */
    virtual uint32_t get_string_offset(uint16_t idx) = 0;
};

}}

#endif
