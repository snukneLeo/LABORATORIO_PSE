#include "System.hh"


System::System( sc_core::sc_module_name ) :
  p("plant"),
  pt("target"),
  c("controller"),
  ct("initiator"),
  ci("iface")
{

  // Controller Interface Side
  ci.outc(sig_tdf_fw);
  c.in(sig_tdf_fw);

  ci.inc(sig_tdf_bw);
  c.out(sig_tdf_bw);

  // Controller Interface Transactor Side
  ct.value_bw( sig_ct_bw );
  ci.outp( sig_ct_bw );

  ct.value_fw( sig_ct_fw );
  ci.inp( sig_ct_fw );

  // Transactors Connection
  ct.initiator_socket( pt.target_socket );
 
  // Plant Transactor Side
  pt.value_bw( sig_pt_bw );
  p.in( sig_pt_bw );

  pt.value_fw( sig_pt_fw );
  p.out( sig_pt_fw );


}

System::~System()
{
}
