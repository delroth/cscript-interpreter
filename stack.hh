#ifndef __STACK_HH_
# define __STACK_HH_

# include "exception.hh"

# include <algorithm>
# include <boost/array.hpp>
# include <cstdint>

namespace cscript {

class stack_exception : public exception
{
public:
    stack_exception(const std::string& message) : exception(message)
    {
    }
};

class stack
{
public:
    /**
     * The maximum number of elements in the stack.
     */
    static const uint32_t MAX_SIZE = 0x200;

    /**
     * Constructs a new stack object.
     */
    stack() : top_(MAX_SIZE), frame_base_(MAX_SIZE)
    {
    }

    /**
     * Pushes a value onto the stack.
     */
    void push(uint32_t val)
    {
        if (top_ == 0)
            throw stack_exception("stack overflow while pushing");
        arr_[--top_] = val;
    }

    uint32_t pop()
    {
        if (top_ == MAX_SIZE)
            throw stack_exception("stack underflow while popping");
        return arr_[top_++];
    }

    void reserve(uint32_t size)
    {
        if (top_ < size)
            throw stack_exception("stack overflow while reserving");
        top_ -= size;
    }

    void unreserve(uint32_t size)
    {
        if (top_ + size > MAX_SIZE)
            throw stack_exception("stack underflow while unreserving");
        top_ += size;
    }

private:
    /**
     * The array containing the stack values.
     */
    boost::array<uint32_t, MAX_SIZE> arr_;

    /**
     * Index of the stack current top.
     */
    uint32_t top_;

    /**
     * Index of the stack current frame base.
     */
    uint32_t frame_base_;
};

};

#endif
