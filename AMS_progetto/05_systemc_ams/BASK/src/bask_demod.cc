#include "bask_demod.hh"

bask_demod::bask_demod( sc_core::sc_module_name _name ):
    sc_core::sc_module( _name ),
    in("in"),
    out("out"),
    rc("rc"),
    lp("lp", 3.3e6, 1.0),
    sp("sp"),
    rc_out("rc_out"),
    lp_out("lp_out")
{
    rc.in(in);
    rc.out(rc_out);

    lp.in(rc_out);
    lp.out(lp_out);

    sp.in(lp_out);
    sp.out(out);
}

