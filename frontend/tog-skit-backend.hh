#ifndef __FRONTEND_TOG_SKIT_BACKEND_HH_
# define __FRONTEND_TOG_SKIT_BACKEND_HH_

# include <tog-skit/backend.hh>

namespace frontend { namespace tog_skit {

class backend : public cscript::tog_skit::backend
{
public:
    virtual char* get_stringtable_base();
    virtual uint32_t get_string_offset(uint16_t idx);
};

}}

#endif
