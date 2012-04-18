#include "tog-skit-backend.hh"

#include <endian.hh>

namespace frontend { namespace tog_skit {

char* backend::get_stringtable_base()
{
    return scs_.data;
}

uint32_t backend::get_string_offset(uint16_t idx)
{
    const uint32_t* ptr = (const uint32_t*)scs_.data;
    uint32_t nstrings = cscript::endian::swap(*ptr++);
    if (idx >= nstrings)
        return 0;

    for (uint16_t i = 0; i < idx; ++i)
        ptr++;

    return cscript::endian::swap(*ptr);
}

}}
