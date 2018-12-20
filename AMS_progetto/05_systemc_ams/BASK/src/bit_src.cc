#include "bit_src.hh"

bit_src::bit_src( sc_core::sc_module_name _name ) :
  sca_tdf::sca_module( _name ),
  out( "out" )
{
}

void bit_src::processing()
{
  out.write( (bool) (std::rand()%2) );
}
