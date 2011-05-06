#ifndef __BASIC_CSCRIPT_HH_
# define __BASIC_CSCRIPT_HH_

# include "cscript.hh"

namespace cscript {

class basic_cscript : public cscript
{
public:
    basic_cscript() : cscript()
    {
    }

    basic_cscript(const char* buffer, size_t size) : cscript(buffer, size)
    {
    }
    
    virtual void handle_syscall(uint16_t syscall,
                                const std::vector<uint32_t>& args);
};

}

#endif
