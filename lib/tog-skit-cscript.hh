#ifndef __TOG_SKIT_CSCRIPT_HH_
# define __TOG_SKIT_CSCRIPT_HH_

# include "cscript.hh"

namespace cscript {

class tog_skit_cscript : public cscript
{
public:
    tog_skit_cscript() = delete;

    tog_skit_cscript(const char* buffer, size_t size)
        : cscript(buffer, size)
    {
    }

    virtual void handle_syscall(uint16_t syscall,
                                const std::vector<uint32_t>& args);
};

}

#endif
