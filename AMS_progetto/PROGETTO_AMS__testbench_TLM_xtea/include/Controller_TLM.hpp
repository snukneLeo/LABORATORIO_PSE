#ifndef TLM_CONTROLLER_HH
#define TLM_CONTROLLER_HH

#include "struct.hh"
#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/tlm_quantumkeeper.h>


class TLM_controller : public sc_module, public virtual tlm::tlm_bw_transport_if<>,tlm::tlm_fw_transport_if<>
{
  public:
    SC_HAS_PROCESS( TLM_controller );

    double waterLevel;
    double thresh;


    virtual void invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range );
    virtual tlm::tlm_sync_enum nb_transport_bw(tlm::tlm_generic_payload &trans,tlm::tlm_phase &phase,sc_time &t);
    //funzione usata da initiator per l'invio delle info nel payload
    virtual void b_transport( tlm::tlm_generic_payload &trans, sc_time &t );

    //Funzioni di interfaccia non usate
    virtual bool get_direct_mem_ptr(tlm::tlm_generic_payload &trans, tlm::tlm_dmi &dmi_data);
    virtual tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload &trans, tlm::tlm_phase &phase, sc_time &t);
    virtual unsigned int transport_dbg(tlm::tlm_generic_payload &trans);
    
    void run();
    void xtea_encrypt(int command);

    tlm_utils::tlm_quantumkeeper m_qk;
    tlm::tlm_initiator_socket<> initiator_socket;
    tlm::tlm_target_socket<> target_socket;
    //creo il costruttore in modo che prenda all'inizio chiavi e parole da usare
    TLM_controller( sc_module_name name,
                    sc_uint<32> key0,
                    sc_uint<32> key1,
                    sc_uint<32> key2,
                    sc_uint<32> key3,
                    sc_uint<32> delta);

    private:
        sc_time timing;
        sc_uint<32> word0;
        sc_uint<32> word1;
        sc_uint<32> key0;
        sc_uint<32> key1;
        sc_uint<32> key2;
        sc_uint<32> key3;
        sc_uint<32> delta;


};

#endif
