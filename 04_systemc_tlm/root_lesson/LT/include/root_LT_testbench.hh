#ifndef _root_LT_TESTBENCH_H_
#define _root_LT_TESTBENCH_H_

#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/tlm_quantumkeeper.h>
#include "define_LT.hh"

class root_LT_testbench
  : public sc_module
  , public virtual tlm::tlm_bw_transport_if<>
{

private:

  SC_HAS_PROCESS(root_LT_testbench);

  // functions necessary to be compliant with the TLM standard
  // not used here
  virtual void invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range);
  virtual tlm::tlm_sync_enum nb_transport_bw(tlm::tlm_generic_payload &  trans, tlm::tlm_phase &  phase, sc_time &  t);

  // quantum keeper used for temporal decoupling
  tlm_utils::tlm_quantumkeeper m_qk;

  void run();

public:

  // TLM socket
  tlm::tlm_initiator_socket<> initiator_socket;

  // constructor
  root_LT_testbench(sc_module_name name);

};

#endif
