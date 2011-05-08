#ifndef __SKIT_CSCRIPT_HH_
# define __SKIT_CSCRIPT_HH_

# include "cscript.hh"
# include "skit/backend.hh"

namespace cscript {

class skit_cscript : public cscript
{
public:
    skit_cscript() = delete;

    skit_cscript(skit::backend* backend, const char* buffer, size_t size)
        : cscript(buffer, size), backend_(backend)
    {
    }

    virtual void handle_syscall(uint16_t syscall,
                                const std::vector<uint32_t>& args);

    skit::backend& backend() { return *backend_; }
    const skit::backend& backend() const { return *backend_; }

private:
    skit::backend* backend_;
};

}

#endif
