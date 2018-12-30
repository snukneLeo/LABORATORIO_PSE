#ifndef _xtea_UT_TESTBENCH_H_
#define _xtea_UT_TESTBENCH_H_

#include <systemc.h>
#include <tlm.h>
#include "define_UT.hh"

class xtea_UT_testbench
  : public sc_module
  , public virtual tlm::tlm_bw_transport_if<>
{

private:

  SC_HAS_PROCESS(xtea_UT_testbench);

  //funzioni definite in quanto la classe richiede questi metodi
  virtual void invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range);
  virtual tlm::tlm_sync_enum nb_transport_bw(tlm::tlm_generic_payload &  trans, tlm::tlm_phase &  phase, sc_time &  t);

  // metodo del thread
  void run();

public:

  // TLM socket usato da initiator
  tlm::tlm_initiator_socket<> initiator_socket;

  // costruttore
  xtea_UT_testbench(sc_module_name name);

};

#endif
