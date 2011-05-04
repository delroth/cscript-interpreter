#ifndef __UTILS_HH_
# define __UTILS_HH_

namespace cscript { namespace utils {

inline float float_from_u32(uint32_t u32)
{
    union
    {
        float f;
        uint32_t u;
    } bitcaster;

    bitcaster.u = u32;
    return bitcaster.f;
}

}}

#endif
