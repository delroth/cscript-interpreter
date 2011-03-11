#include "address.hh"

namespace cscript { namespace address {

/**
 * Metaprogramming to code the get_ptr function without repeating code.
 */
template <typename T>
struct Const
{
    typedef const T type;
};

template <typename T>
struct Normal
{
    typedef T type;
};

template <template <typename> class ConstQual>
typename ConstQual<char>::type* generic_get_ptr(
                        typename ConstQual<cscript>::type& script,
                        uint32_t address)
{
    if (address & DATA_FLAG)
    {
        uint32_t off = (address & DATA_OFF_MASK) >> DATA_OFF_SHIFT;
        return script.data_at(off);
    }
    else if (address & STACK_FLAG)
    {
        uint16_t off = (address & STACK_OFF_MASK) >> STACK_OFF_SHIFT;
        uint16_t tid = (address & STACK_THREAD_MASK) >> STACK_THREAD_SHIFT;
        auto ptr = &script.thread(tid).stk.at(off);
        return (typename ConstQual<char>::type*)(ptr);
    }
    else
        return 0;
}

char* get_ptr(cscript& script, uint32_t address)
{
    return generic_get_ptr<Normal>(script, address);
}

const char* get_ptr(const cscript& script, uint32_t address)
{
    return generic_get_ptr<Const>(script, address);
}

}}
