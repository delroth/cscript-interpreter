#ifndef __SCRIPT_LOADER_HH_
# define __SCRIPT_LOADER_HH_

# include <cscript.hh>
# include <string>

namespace cscript { namespace tests {

/**
 * Utility class to be used in the test fixtures.
 */
struct script_loader
{
    /**
     * Initializes the interpreter by loading the file returned by the virtual
     * file() method.
     */
    script_loader(const std::string& file);

    /**
     * The loaded script object.
     */
    cscript interp;
};

}}

#endif
