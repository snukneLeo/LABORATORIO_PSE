#ifndef TRANSATTORE_FROM_RTL_TO_TLM
#define TRANSATTORE_FROM_RTL_TO_TLM


#include <tlm.h>
#include "struct.hh"
#include "systemc.h"
#include "tlm_utils/tlm_quantumkeeper.h"


class RTL_TO_TLM : public sc_module, public virtual tlm::tlm_bw_transport_if<>
{
  public:
    tlm::tlm_initiator_socket<> initiator_socket;
    virtual void invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range);
    virtual tlm::tlm_sync_enum nb_transport_bw(tlm::tlm_generic_payload &trans, tlm::tlm_phase &phase, sc_time &t);
    SC_HAS_PROCESS(RTL_TO_TLM);
    RTL_TO_TLM(sc_module_name name);
    // RTL Interface input
    sc_in < double > waterLevelInput_rtl;

    private:
      //metodi
      void run();
      void trasduce();
      tlm_utils::tlm_quantumkeeper m_qk;
};


#endif
