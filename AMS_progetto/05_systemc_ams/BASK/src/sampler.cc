#include "sampler.hh"

sampler::sampler( sc_core::sc_module_name _name) :
    sca_tdf::sca_module( _name ),
    in("in"),
    out("out"),
    rate(40),
    threshold(0)
{
}

void sampler::set_attributes()
{
    in.set_rate( rate );
    sample_pos = (unsigned long) std::ceil( 2.0 * (double)rate/3.0 );
}

void sampler::processing()
{
    if( in.read( sample_pos ) > threshold )
        out.write( true );
    else
        out.write( false );
}
