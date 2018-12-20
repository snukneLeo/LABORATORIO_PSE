#include "ControllerIFace.hh"

controller_iface::controller_iface( sc_core::sc_module_name ) :
  inc( "inc" ),
  outc( "outc" ),
  inp( "inp" ),
  outp( "outp" )
{
}

controller_iface::~controller_iface()
{
}


void controller_iface::processing()
{
  outc.write( inp.read() );
  outp.write( inc.read() );
}

void controller_iface::set_attribute()
{

}
