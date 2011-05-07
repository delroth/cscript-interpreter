#ifndef __SKIT_BACKEND_HH_
# define __SKIT_BACKEND_HH_

#include <cstdint>
#include <string>

namespace cscript { namespace skit {

/**
 * The backend of a skit_cscript, which is called by all the syscalls when a
 * sophisticated operation is to be done.
 */
class backend
{
public:
    /**
     * Inits the backend. First method called when starting a skit.
     *
     * @param skit_id The identifier of the skit. For example, "FC01_001".
     */
    virtual void init(const std::string& skit_id) = 0;

    /**
     * Sets the given boolean to true when the skit is ready to go.
     */
    virtual void wait_start(bool* ptr) = 0;

    /**
     * Initializes a character portait.
     *
     * @param id The integer representing this character.
     * @param face The TPL to use as the character portait.
     * @param x The x position of the portait on the screen.
     * @param y The y position of the portrait on the screen.
     * @param subface The sub-face id to display.
     */
    virtual void init_char(uint32_t id, uint32_t face,
                           float x, float y, uint32_t subface) = 0;

    /**
     * Sets a character portait scale.
     *
     * @param id The integer representing this character.
     * @param scale A floating point between 0 and 1 representing how to scale.
     */
    virtual void scale_char(uint32_t id, float scale) = 0;

    /**
     * Gets the current position of a character.
     *
     * @param id The character id.
     * @param x The reference where the x position should be placed.
     * @param y The reference where the y position should be placed.
     */
    virtual void get_char_pos(uint32_t id, float& x, float& y) = 0;

    /**
     * Sets where a character should be in n frames. In other words, sets the
     * end point of an n frame movement interpolation.
     *
     * @param id The character id.
     * @param x The x position endpoint.
     * @param y The y position endpoint.
     * @param n The number of frames.
     */
    virtual void set_char_pos(uint32_t id, float x, float y, uint32_t n) = 0;

    /**
     * Sets the skit subtitle with a given text.
     *
     * @param speaker The character currently speaking.
     * @param text The text currently being spoken.
     */
    virtual void set_subtitle(const std::string& speaker,
                              const std::string& text) = 0;
};

}}

#endif
