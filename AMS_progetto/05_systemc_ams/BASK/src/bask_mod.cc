#include "bask_mod.hh"

bask_mod::bask_mod( sc_core::sc_module_name _name ) :
  sc_core::sc_module( _name ),
  in( "in" ),
  out( "out" ),
  sine( "sine", 1.0, 1.0e7, sca_core::sca_time( 5.0, sc_core::SC_NS ) ),
  mix( "mix" )
  {
    sine.out( carrier );
    mix.in_wav( carrier );
    mix.in_bin( in );
    mix.out( out );
  }

