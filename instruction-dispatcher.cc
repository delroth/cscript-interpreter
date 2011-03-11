#include "instruction-dispatcher.hh"

#include <boost/foreach.hpp>

namespace cscript { namespace instruction {

dispatcher& dispatcher::get()
{
    static dispatcher instance;
    return instance;
}

void dispatcher::register_handler(uint32_t value, uint32_t mask, handler h)
{
    dispatch_table_.push_back(dispatch_infos(value, mask, h));
}

boost::optional<handler> dispatcher::get_handler(uint32_t opcode)
{
    BOOST_FOREACH (const dispatch_infos& inf, dispatch_table_)
    {
        if ((opcode & inf.get<1>()) == inf.get<0>())
            return boost::optional<handler>(inf.get<2>());
    }

    return boost::optional<handler>();
}

}}
