#ifndef CONTROLLER_TRANSACTOR_HH
#define CONTROLLER_TRANSACTOR_HH

#include "define_LT.hh"
#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/tlm_quantumkeeper.h>


class ControllerTransactor :
  public sc_module,
  public virtual tlm::tlm_bw_transport_if<>
{

  private:
    SC_HAS_PROCESS( ControllerTransactor );

    virtual void invalidate_direct_mem_ptr(
        uint64 start_range, uint64 end_range );

    virtual tlm::tlm_sync_enum nb_transport_bw(
        tlm::tlm_generic_payload& trans,
        tlm::tlm_phase& phase,
        sc_time& t);

    void run();
    
    tlm_utils::tlm_quantumkeeper m_qk;


  public:
    tlm::tlm_initiator_socket<> initiator_socket;
    ControllerTransactor( sc_module_name name );

    //RTL Interface
    sc_in< double > value_bw;
    sc_out< double > value_fw;


};

#endif //CONTROLLER_TRANSACTOR_HH
