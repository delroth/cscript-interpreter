#ifndef __TOS2_SKIT_CSCRIPT_HH_
# define __TOS2_SKIT_CSCRIPT_HH_

# include "cscript.hh"
# include "tos2-skit/backend.hh"

namespace cscript {

class tos2_skit_cscript : public cscript
{
public:
    tos2_skit_cscript() = delete;

    tos2_skit_cscript(tos2_skit::backend* backend, const char* buffer,
                      size_t size)
        : cscript(buffer, size), backend_(backend)
    {
    }

    virtual void handle_syscall(uint16_t syscall,
                                const std::vector<uint32_t>& args);

    tos2_skit::backend& backend() { return *backend_; }
    const tos2_skit::backend& backend() const { return *backend_; }

private:
    tos2_skit::backend* backend_;
};

}

#endif
