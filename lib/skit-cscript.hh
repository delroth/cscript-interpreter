#ifndef __SKIT_CSCRIPT_HH_
# define __SKIT_CSCRIPT_HH_

# include "cscript.hh"

namespace cscript {

class skit_cscript : public cscript
{
public:
    skit_cscript() : cscript()
    {
    }

    skit_cscript(const char* buffer, size_t size) : cscript(buffer, size)
    {
    }

    virtual void handle_syscall(uint16_t syscall);
};

}

#endif
