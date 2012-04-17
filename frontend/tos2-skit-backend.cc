#include "tos2-skit-backend.hh"

#include <iostream>

namespace frontend { namespace tos2_skit {

void backend::init(const std::string& skit_id)
{
    std::cerr << "[skit] init skit " << skit_id << std::endl;
}

void backend::wait_start(bool* ptr)
{
    std::cerr << "[skit] waiting for the skit start" << std::endl;
    *ptr = true;
}

void backend::init_char(uint32_t id, uint32_t face,
                        float x, float y, uint32_t subface)
{
    std::cerr << "[skit] initializing character " << id << std::endl;
    characters_[id] = { face, subface, x, y };
}

void backend::scale_char(uint32_t id, float scale)
{
    std::cerr << "[skit] scaling " << id << " to " << scale << std::endl;
}

void backend::get_char_pos(uint32_t id, float& x, float& y)
{
    std::cerr << "[skit] getting position of character " << id << std::endl;
    if (characters_.find(id) == characters_.end())
        return;

    x = characters_[id].x;
    y = characters_[id].y;
}

void backend::set_char_pos(uint32_t id, float x, float y, uint32_t n)
{
    std::cerr << "[skit] setting position of character " << id << " to ";
    std::cerr << "(" << x << ", " << y << ") in " << n << " frames" << std::endl;

    characters_[id].x = x;
    characters_[id].y = y;
}

void backend::set_subtitle(const std::string& speaker,
                           const std::string& text)
{
    std::cerr << "[skit] setting subtitle: " << speaker << ": " << text << std::endl;
}

}}
