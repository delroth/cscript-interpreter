#include "type.hh"
#include "variable.hh"

namespace cscript {

uint32_t variable::cast_to(uint16_t wanted_type)
{
    if (wanted_type == this->type) // no conversion to do
        return this->value.u32;

    bool i_am_float = (this->type & 0xFF) == type::FLOAT;
    bool want_float = (wanted_type & 0xFF) == type::FLOAT;

    if (i_am_float == want_float) // again, no conversion
        return this->value.u32;

    if (i_am_float)
    {
        return this->value.f32;
    }

    bool i_am_signed = (this->type & 0xFF) == type::SCHAR ||
                       (this->type & 0xFF) == type::SHALF ||
                       (this->type & 0xFF) == type::SWORD;

    variable::value_type bitcaster;

    if (i_am_signed)
        bitcaster.f32 = this->value.s32;
    else
        bitcaster.f32 = this->value.u32;

    return bitcaster.u32;
}

}
