#ifndef __FRONTEND_SKIT_BACKEND_HH_
# define __FRONTEND_SKIT_BACKEND_HH_

# include <map>
# include <skit/backend.hh>

namespace frontend { namespace skit {

struct character
{
    uint32_t face, subface;
    float x, y;
};

class backend : public cscript::skit::backend
{
public:
    virtual void init(const std::string& skit_id);
    virtual void wait_start(bool* ptr);
    virtual void init_char(uint32_t id, uint32_t face,
                           float x, float y, uint32_t subface);
    virtual void scale_char(uint32_t id, float scale);
    virtual void get_char_pos(uint32_t id, float& x, float& y);
    virtual void set_char_pos(uint32_t id, float x, float y, uint32_t n);
    virtual void set_subtitle(const std::string& speaker,
                              const std::string& text);

private:
    std::map<uint32_t, character> characters_;
};

}}

#endif
