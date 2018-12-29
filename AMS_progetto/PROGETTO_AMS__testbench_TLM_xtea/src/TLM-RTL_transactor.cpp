#include "TLM-RTL_transactor.hpp"
#include "systemc.h"

TLM_TO_RTL::TLM_TO_RTL( sc_module_name name ) :
  sc_module( name ),
  target_socket( "target_socket" )
{
  target_socket( *this );

  SC_THREAD(transduce);
  sensitive << clock.pos();
}

void TLM_TO_RTL::b_transport(tlm::tlm_generic_payload &trans,sc_time &t )
{
  //implementation of the b_transport
  valvola = *((valve*) trans.get_data_ptr());
  traduce.notify();
  wait(end_traduce);
}

void TLM_TO_RTL::transduce()
{
  while(true)
  {
    wait(traduce);
    reset.write(1);
    wait();
    reset.write(0);
    wait();
    mode.write(1);
    key0.write(valvola.key0);
    key1.write(valvola.key1);
    key2.write(valvola.key2);
    key3.write(valvola.key3);
    word0.write(valvola.word0);
    word1.write(valvola.word1);
    din_rdy.write(1);
    wait();
    din_rdy.write(0);
    end_traduce.notify();
    threshold.write(valvola.tresholding);
    wait();
  }
}

bool TLM_TO_RTL::get_direct_mem_ptr(tlm::tlm_generic_payload &trans, tlm::tlm_dmi &dmi_data)
{
    return false;
}

tlm::tlm_sync_enum TLM_TO_RTL::nb_transport_fw(tlm::tlm_generic_payload &trans, tlm::tlm_phase &phase, sc_time &t)
{
    return tlm::TLM_COMPLETED;
}

unsigned int TLM_TO_RTL::transport_dbg(tlm::tlm_generic_payload &trans)
{
    return 0;
}


