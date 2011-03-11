#ifndef __ENDIAN_HH_
# define __ENDIAN_HH_

# include <boost/detail/endian.hpp>
# include <cstdint>

namespace cscript { namespace endian {

inline uint16_t swap(uint16_t n)
{
    return (n >> 8) | ((n & 0xFF) << 8);
}

inline uint32_t swap(uint32_t n)
{
    return swap((uint16_t)(n >> 16)) | (swap((uint16_t)(n & 0xFFFF)) << 16);
}

inline uint32_t from_big(uint32_t n)
{
# ifdef BOOST_LITTLE_ENDIAN
    return swap(n);
# else
    return n;
# endif
}

inline uint16_t from_big(uint16_t n)
{
# ifdef BOOST_LITTLE_ENDIAN
    return swap(n);
# else
    return n;
# endif
}

}}

#endif
