#include "type.hh"

namespace cscript { namespace type {

bool trivially_integer(uint16_t type)
{
    if (type & type::POINTER || type & type::POINTER2)
        return true;
    if ((type & 0xF) != type::FLOAT)
        return true;
    return false;
}

}}
