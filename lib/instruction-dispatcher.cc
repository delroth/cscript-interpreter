#include "instruction-dispatcher.hh"

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
    for (const dispatch_infos& inf : dispatch_table_)
    {
        if ((opcode & std::get<1>(inf)) == std::get<0>(inf))
            return boost::optional<handler>(std::get<2>(inf));
    }

    return boost::optional<handler>();
}

}}
