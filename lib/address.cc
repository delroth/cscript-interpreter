#include "address.hh"
#include "endian.hh"

#include <boost/mpl/identity.hpp>
#include <boost/type_traits/add_const.hpp>

namespace cscript { namespace address {

template <template <typename> class trait>
typename trait<char>::type* generic_get_ptr(
                        typename trait<cscript>::type& script,
                        uint32_t address)
{
    if (is_external_addr(address))
    {
        uint16_t id = (address & EXTERNAL_ID_MASK) >> EXTERNAL_ID_SHIFT;
        uint16_t off = (address & EXTERNAL_OFF_MASK) >> EXTERNAL_OFF_SHIFT;
        return script.get_external_pointer(id) + off;
    }
    else if (is_data_addr(address))
    {
        uint32_t off = (address & DATA_OFF_MASK) >> DATA_OFF_SHIFT;
        return script.data_at(off);
    }
    else if (is_stack_addr(address))
    {
        uint16_t off = (address & STACK_OFF_MASK) >> STACK_OFF_SHIFT;
        uint16_t tid = (address & STACK_THREAD_MASK) >> STACK_THREAD_SHIFT;
        auto ptr = &script.thread(tid).stk.at(off);
        return (typename trait<char>::type*)(ptr);
    }
    else
        return 0;
}

char* get_ptr(cscript& script, uint32_t address)
{
    return generic_get_ptr<boost::mpl::identity>(script, address);
}

const char* get_ptr(const cscript& script, uint32_t address)
{
    return generic_get_ptr<boost::add_const>(script, address);
}

uint32_t uword_at(cscript& script, uint32_t address)
{
    const char* ptr = get_ptr(script, address);
    uint32_t u = *((const uint32_t*)ptr);
    if (is_external_addr(address) || is_data_addr(address))
        u = endian::from_big(u);
    return u;
}

uint32_t offset(uint32_t address, int32_t off)
{
    if (is_stack_addr(address))
    {
        if (off % 4 != 0)
            throw exception("offseting a stack addr by a non 4-aligned val");
        off /= 4;
    }

    return address + off;
}

}}
