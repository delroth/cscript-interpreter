#ifndef __INSTRUCTION_DISPATCHER_HH_
# define __INSTRUCTION_DISPATCHER_HH_

# include "instruction-handler.hh"

# include <boost/optional.hpp>
# include <boost/tuple/tuple.hpp>
# include <cstdint>
# include <vector>

namespace cscript { namespace instruction {

class dispatcher
{
public:
    /**
     * Getter for the dispatcher singleton object.
     */
    static dispatcher& get();

    /**
     * Register an instruction handler based on a mask and a value. The handler
     * matches an instruction if opcode & mask == value.
     */
    void register_handler(uint32_t value, uint32_t mask, handler h);

    /**
     * Get a handler for the instruction if available, or nothing if no
     * appropriate handler can be found.
     */
    boost::optional<handler> get_handler(uint32_t opcode);

private:
    /**
     * Private constructor as this class is only used for one instance.
     */
    dispatcher()
    {
    }

    /**
     * The type of informations used to dispatch an instruction to its handler.
     * The three tuple arguments are those passed to register_handler.
     */
    typedef boost::tuple<uint32_t, uint32_t, handler> dispatch_infos;

    /**
     * The dispatch table, which contains everything needed to dispatch an
     * instruction.
     */
    std::vector<dispatch_infos> dispatch_table_;
};

}}

#endif
