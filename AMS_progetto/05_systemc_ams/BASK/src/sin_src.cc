#include "sin_src.hh"

sin_src::sin_src( 
        sc_core::sc_module_name nm,
        double ampl_ = 1.0,
        double freq_ = 1.0e3,
        sca_core::sca_time Tm_ = sca_core::sca_time( 0.125, sc_core::SC_MS )
        ) :
    out( "out" ),
    ampl( ampl_ ),
    freq( freq_ ),
    Tm( Tm_ )
{
}

void sin_src::set_attributes()
{
    set_timestep( Tm );
}

void sin_src::processing()
{
    double t = get_time().to_seconds();
    out.write( ampl * std::sin( 2.0 * M_PI * freq * t ));
}
