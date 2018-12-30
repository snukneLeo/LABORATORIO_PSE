#ifndef _xtea_LT_TESTBENCH_H_
#define _xtea_LT_TESTBENCH_H_

#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/tlm_quantumkeeper.h>
#include "define_LT.hh"

class xtea_LT_testbench
  : public sc_module
  , public virtual tlm::tlm_bw_transport_if<>
{

private:

  SC_HAS_PROCESS(xtea_LT_testbench);

  //funzioni definite in quanto la classe richiede questi metodi
  virtual void invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range);
  virtual tlm::tlm_sync_enum nb_transport_bw(tlm::tlm_generic_payload &  trans, tlm::tlm_phase &  phase, sc_time &  t);

  // quantum keeper usato per il temporal decoupling
  tlm_utils::tlm_quantumkeeper m_qk;

  //metodo run della thread
  void run();

public:

  // TLM socket
  tlm::tlm_initiator_socket<> initiator_socket;

  // costruttore
  xtea_LT_testbench(sc_module_name name);

};

#endif
