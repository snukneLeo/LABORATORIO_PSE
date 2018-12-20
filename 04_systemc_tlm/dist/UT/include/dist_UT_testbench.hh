#ifndef _dist_UT_TESTBENCH_H_
#define _dist_UT_TESTBENCH_H_

#include <systemc.h>
#include <tlm.h>
#include "define_UT.hh"

class dist_UT_testbench
  : public sc_module
  , public virtual tlm::tlm_bw_transport_if<>
{

private:

  unsigned int photo[512];
  
  SC_HAS_PROCESS(dist_UT_testbench);

  virtual void invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range);

  virtual tlm::tlm_sync_enum nb_transport_bw(tlm::tlm_generic_payload &  trans, tlm::tlm_phase &  phase, sc_time &  t);

  void run();

public:

  tlm::tlm_initiator_socket<> initiator_socket;

  dist_UT_testbench(sc_module_name name);

};

#endif
