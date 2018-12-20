#include "rectifier.hh"

rectifier::rectifier( sc_core::sc_module_name _name ) :
    sca_tdf::sca_module( _name ),
    in("in"),
    out("out")
{
}

void rectifier::processing()
{
    out.write( std::abs( in.read() ));
}
