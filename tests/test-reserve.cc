#include "script-loader.hh"

#include <BoostTestTargetConfig.h>
#include <cscript.hh>

struct reserve_script_loader : public cscript::tests::script_loader
{
    reserve_script_loader() :
        cscript::tests::script_loader("tests/data/reserve.so")
    {
    }
};

BOOST_FIXTURE_TEST_CASE(instr_reserve, reserve_script_loader)
{
    uint32_t stack_top = interp.curr_thread().stk.top();
    interp.run_one_instr(); // RESERVE 0x40
    uint32_t new_stack_top = interp.curr_thread().stk.top();
    BOOST_CHECK_EQUAL(new_stack_top, stack_top - 0x10); // 0x40 / 4

    // Check that RESERVE 0x1000 fails
    BOOST_CHECK_THROW(interp.run_one_instr(), cscript::stack_exception);
}
