#include "plant_lsf.hh"

plant::plant( sc_core::sc_module_name ) :
  x("x"),
  y("y")
{
  x.inp(in);
  x.y(sig);

  x.set_timestep( 1, sc_core::SC_MS );

  y.x(sig);
  y.outp(out);
}

plant::~plant()
{
}
