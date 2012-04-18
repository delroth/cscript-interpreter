#ifndef __FRONTEND_TOG_SKIT_BACKEND_HH_
# define __FRONTEND_TOG_SKIT_BACKEND_HH_

# include <tog-skit/backend.hh>

# include <boost/iostreams/device/mapped_file.hpp>

namespace frontend { namespace tog_skit {

struct scs_file
{
    scs_file(const std::string& path)
        : mapped_file_(path), data(const_cast<char*>(mapped_file_.data()))
        , size(mapped_file_.size())
    {
    }

    boost::iostreams::mapped_file_source mapped_file_;
    char* data;
    size_t size;
};

class backend : public cscript::tog_skit::backend
{
public:
    backend(const std::string& scs_path) : scs_(scs_path) {}

    virtual char* get_stringtable_base();
    virtual uint32_t get_string_offset(uint16_t idx);

private:
    scs_file scs_;
};

}}

#endif
