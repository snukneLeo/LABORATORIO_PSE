#include "ControllerTransactor.hh"

ControllerTransactor::ControllerTransactor( sc_module_name name ) :
  sc_module( name )
{
  initiator_socket(*this);
  m_qk.set_global_quantum( sc_time( 20, SC_MS ));
  m_qk.reset();

  SC_THREAD(run);
  sensitive << value_bw;
}

void ControllerTransactor::run()
{
  iostruct packet;
  tlm::tlm_generic_payload payload;
  sc_time local_time = m_qk.get_local_time();
  

  while( true )
  {
    payload.set_data_ptr((unsigned char*) &packet);

    payload.set_write();
    local_time = m_qk.get_local_time();
    

    packet.value_bw = value_bw.read();
    initiator_socket->b_transport( payload, local_time );
    packet = *((iostruct*) payload.get_data_ptr());

    value_fw.write( packet.value_fw );

    wait();
  }
}

void ControllerTransactor::invalidate_direct_mem_ptr(
    uint64 start_range, 
    uint64 end_range)
{
  
}

tlm::tlm_sync_enum ControllerTransactor::nb_transport_bw(
    tlm::tlm_generic_payload &  trans, 
    tlm::tlm_phase &  phase, 
    sc_time &  t)
{
  return tlm::TLM_COMPLETED;
}

