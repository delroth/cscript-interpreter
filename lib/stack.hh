#ifndef __STACK_HH_
# define __STACK_HH_

# include "exception.hh"

# include <array>
# include <cstdint>
# include <iomanip>
# include <ostream>

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
        // Clean the stack
        for (uint32_t i = 0; i < MAX_SIZE; ++i)
            arr_[i] = 0;
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

    /**
     * Returns a reference to a value at a given offset.
     */
    uint32_t& at(uint16_t offset)
    {
        return arr_[offset];
    }

    const uint32_t& at(uint16_t offset) const
    {
        return arr_[offset];
    }

    /**
     * Pushes a new stack frame on the stack.
     */
    void push_frame(uint32_t pc)
    {
        push(pc);
        push(frame_base_);
        frame_base_ = top_;
    }

    /**
     * Restores a stack frame from the stack and returns pc.
     */
    uint32_t pop_frame()
    {
        top_ = frame_base_;
        frame_base_ = pop();
        return pop();
    }

    /**
     * Gets the current frame base index.
     */
    uint32_t frame_base() const
    {
        return frame_base_;
    }

    /**
     * Gets the current stack top index.
     */
    uint32_t top() const
    {
        return top_;
    }

private:
    /**
     * The array containing the stack values.
     */
    std::array<uint32_t, MAX_SIZE> arr_;

    /**
     * Index of the stack current top.
     */
    uint32_t top_;

    /**
     * Index of the stack current frame base.
     */
    uint32_t frame_base_;

    /*
     * Friend dumping function.
     */
    template <typename T>
    friend T& operator<<(T& str, const stack& s);
};

/*
 * Dumping function.
 */
template <typename T>
T& operator<<(T& str, const stack& s)
{
    std::ios_base::fmtflags fmt = str.flags();

    str << "Stack: current top is " << std::hex << s.top_ << " and current "
        << "frame base is " << s.frame_base_ << std::endl;
    str << "  Contents:" << std::endl;

    for (uint32_t i = stack::MAX_SIZE - 1; i >= s.top_; --i)
    {
        str << "    ";
        str << std::hex << std::setfill('0') << std::setw(8);
        str << s.arr_[i] << std::endl;
    }

    str.flags(fmt);
    return str;
}

};

#endif
