#ifndef __INSTRUCTION_HANDLER_HH_
# define __INSTRUCTION_HANDLER_HH_

# include "cscript.hh"

# include <cstdint>

namespace cscript { namespace instruction {

/**
 * The type of an instruction handler.
 */
typedef void (*handler)(cscript&, uint32_t);

}}

#endif
