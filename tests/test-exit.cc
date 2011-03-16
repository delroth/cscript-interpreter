#include "script-loader.hh"

#include <BoostTestTargetConfig.h>
#include <cscript.hh>

struct exit_script_loader : public cscript::tests::script_loader
{
    exit_script_loader() :
        cscript::tests::script_loader("tests/data/simply-exit.so")
    {
    }
};

BOOST_FIXTURE_TEST_CASE(instr_exit, exit_script_loader)
{
    BOOST_CHECK(!interp.done());
    interp.run_one_instr();
    BOOST_CHECK(interp.done());
}
