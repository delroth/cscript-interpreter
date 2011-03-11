#ifndef __SCRATCHPAD_HH_
# define __SCRATCHPAD_HH_

# include "exception.hh"
# include "variable.hh"

# include <boost/array.hpp>
# include <cstdlib>

namespace cscript {

class scratchpad_exception : public exception
{
public:
    scratchpad_exception(const std::string& message) : exception(message)
    {
    }
};

/**
 * The scratchpad is the place where temporary variables are stored and
 * computations are done.
 *
 * It is actually like a stack, but with a limited size (at most MAX_VARIABLES
 * variables can be stored) and encourages to alter directly stored variables
 * instead of pushing/popping.
 */
class scratchpad
{
public:
    /**
     * Maximum number of variables in the scratchpad.
     */
    static const uint32_t MAX_VARIABLES = 0x100;

    /**
     * Constructs a scratchpad object and initializes the current index to 0.
     */
    scratchpad() : idx_(0)
    {
    }

    /**
     * Moves the current index to the next variable in the scratchpad.
     */
    void push()
    {
        if (++idx_ >= MAX_VARIABLES)
            throw scratchpad_exception("scratchpad overflow while pushing");
    }

    /**
     * Moves the current index to the previous variable in the scratchpad.
     */
    void pop()
    {
        if (idx_ == 0)
            throw scratchpad_exception("scratchpad underflow while popping");
        idx_--;
    }

    /**
     * Returns a reference to the n-th variable from the top.
     */
    variable& top(uint32_t n)
    {
        if (idx_ < n)
            throw scratchpad_exception("indexing outside of the scratchpad");
        return vars_[idx_ - n];
    }

    const variable& top(uint32_t n) const
    {
        if (idx_ < n)
            throw scratchpad_exception("indexing outside of the scratchpad");
        return vars_[idx_ - n];
    }

private:
    /**
     * Current index in the stack.
     */
    uint32_t idx_;

    /**
     * Array containing the variables currently stored in the scratchpad.
     */
    boost::array<variable, MAX_VARIABLES> vars_;
};

}

#endif
