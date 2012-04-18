#ifndef __TOG_SKIT_CSCRIPT_HH_
# define __TOG_SKIT_CSCRIPT_HH_

# include "cscript.hh"
# include "tog-skit/backend.hh"

namespace cscript {

class tog_skit_cscript : public cscript
{
public:
    tog_skit_cscript() = delete;

    tog_skit_cscript(tog_skit::backend* backend, const char* buffer,
                     size_t size)
        : cscript(buffer, size), backend_(backend)
    {
    }

    virtual void handle_syscall(uint16_t syscall,
                                const std::vector<uint32_t>& args);

    tog_skit::backend& backend() { return *backend_; }
    const tog_skit::backend& backend() const { return *backend_; }

private:
    tog_skit::backend* backend_;
};

}

#endif
