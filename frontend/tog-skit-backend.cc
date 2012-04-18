#include "tog-skit-backend.hh"

namespace frontend { namespace tog_skit {

char* backend::get_stringtable_base()
{
    return 0;
}

uint32_t backend::get_string_offset(uint16_t idx)
{
    return idx;
}

}}
