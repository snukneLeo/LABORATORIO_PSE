#ifndef TRANSACTOR_TLM_RTL_HPP
#define TRANSACTOR_TLM_RTL_HPP

#include <systemc.h>
#include <tlm.h>
#include "struct.hh"
class Transactor_TLM_RTL :
  public sc_module,
  public virtual tlm::tlm_fw_transport_if<>
{
    public:
        //initiator socket TLM
        tlm::tlm_target_socket<> target_socket;

        //primitiva b_transport
        virtual void b_transport( tlm::tlm_generic_payload& trans, sc_time& t );
        //metodi non usati
        virtual bool get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi & dmi_data );
        virtual tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload& trans,tlm::tlm_phase& phase,sc_time& t);
        virtual unsigned int transport_dbg(tlm::tlm_generic_payload &trans);
        sc_event traduce, end_traduce;
        //costruttore
        Transactor_TLM_RTL(sc_module_name name);

        // RTL interfacccia per la conversione da TLM a RTL
        sc_in<sc_logic> clock;
        sc_out<double> threshold;
        sc_out<sc_uint<32> > word0;
        sc_out<sc_uint<32> > word1;
        sc_out<sc_uint<32> > key1;
        sc_out<sc_uint<32> > key2;
        sc_out<sc_uint<32> > key3;
        sc_out<sc_uint<32> > key4;
        sc_out<sc_uint<1> > mode;
        sc_out<bool> din_rdy;
        sc_out<bool> reset;

        //metodo
        void transduce();
        SC_HAS_PROCESS(Transactor_TLM_RTL);
        //struttura
        valvola_s valve_commands;
};

#endif 