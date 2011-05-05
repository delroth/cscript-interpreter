#include "address.hh"
#include "exception.hh"
#include "type.hh"
#include "variable.hh"

#include <map>
#include <set>

namespace cscript {

uint32_t variable::cast_to(uint16_t wanted_type) const
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

bool variable::boolean_value() const
{
    if ((this->type & type::POINTER) || (this->type & type::POINTER2))
        return true;
    else
        return !!(this->value.u32);
}

// This is so ugly...
#define FLIP_ENDIAN(v) (([&]() { \
    if (this->address & address::DATA_FLAG) \
        return endian::from_big(v); \
    else \
        return v; \
    })())

uint32_t variable::read_value_from_addr(const cscript& interp) const
{
    const static std::set<uint16_t> imm_types = {
        type::VOID,
        type::ADDR
    };

    if (this->type & type::IMMEDIATE)
        return this->value.u32;
    else if (imm_types.find(this->type & 0xF) != imm_types.end())
        return this->value.u32;
    else
    {
        const char* ptr = address::get_ptr(interp, this->address);
        uint16_t t = this->type & 0xF;
        variable::value_type v;

        switch (t)
        {
        case type::UCHAR:
            v.u32 = *((const uint8_t*)ptr);
            break;

        case type::SCHAR:
            v.s32 = *((const int8_t*)ptr);
            break;

        case type::UHALF:
            v.u32 = FLIP_ENDIAN(*((const uint16_t*)ptr));
            break;

        case type::SHALF:
            v.s32 = (int16_t)FLIP_ENDIAN(*((const uint16_t*)ptr));
            break;

        case type::FLOAT:
        case type::UWORD:
            v.u32 = FLIP_ENDIAN(*((const uint32_t*)ptr));
            break;

        case type::SWORD:
            v.s32 = (int32_t)FLIP_ENDIAN(*((const uint32_t*)ptr));
            break;

        default:
            throw exception("reading an unknown value type from memory");
        }

        return v.u32;
    }
}

void variable::write_value_to_addr(cscript& interp) const
{
    if (this->type & type::IMMEDIATE)
        return;

    char* ptr = address::get_ptr(interp, this->address);
    if (this->type & type::POINTER || this->type & type::POINTER3)
    {
        *((uint32_t*)ptr) = FLIP_ENDIAN(this->value.u32);
        return;
    }

    switch (this->type & 0xF)
    {
    case type::SCHAR:
    case type::UCHAR:
        *((uint8_t*)ptr) = this->value.u32;
        break;

    case type::SHALF:
    case type::UHALF:
        *((uint16_t*)ptr) = FLIP_ENDIAN((uint16_t)this->value.u32);
        break;

    case type::SWORD:
    case type::UWORD:
    case type::FLOAT:
        *((uint32_t*)ptr) = FLIP_ENDIAN(this->value.u32);
        break;
    }
}

}
