#ifndef PLANT_TRANSACTOR_HH
#define PLANT_TRANSACTOR_HH


#include <tlm.h>
#include "define_LT.hh"

#include "params.hh"

class PlantTransactor :
  public sc_module,
  public virtual tlm::tlm_fw_transport_if<>
{
  public:
    tlm::tlm_target_socket<> target_socket;

    virtual void b_transport( tlm::tlm_generic_payload& trans, sc_time& t );
    virtual bool get_direct_mem_ptr(
        tlm::tlm_generic_payload& trans, tlm::tlm_dmi & dmi_data );

    virtual unsigned int transport_dbg( tlm::tlm_generic_payload& trans );

    void end_of_elaboration();
    void reset();

    virtual tlm::tlm_sync_enum nb_transport_fw(
        tlm::tlm_generic_payload& trans,
        tlm::tlm_phase& phase,
        sc_time& t);

    iostruct ioDataStruct;

    tlm::tlm_generic_payload* pending_transaction;

    sc_time timing_annotation;

    void transduce();

    SC_HAS_PROCESS(PlantTransactor);

    PlantTransactor(sc_module_name name);
    ~PlantTransactor();

    // RTL Interface
    sc_in< double > value_fw;
    sc_out< double > value_bw;

  protected:
#ifdef TRACING
    FILE * log;
    void _trace();
#endif

};


#endif //PLANT_TRANSACTOR_HH
