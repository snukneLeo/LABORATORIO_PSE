#include "RTL-TLM_transactor.hpp"

RTL_TO_TLM::RTL_TO_TLM( sc_module_name name ) : sc_module( name )
{
  initiator_socket(*this);
  m_qk.set_global_quantum(sc_time(100, SC_NS));
  m_qk.reset();
  SC_THREAD(run);
}


void RTL_TO_TLM::run()
{
  while(true)
  {
    wait(5,SC_SEC);
    trasduce();
  }
}

void RTL_TO_TLM::trasduce()
{
  waterTank water_packet;
  tlm::tlm_generic_payload payload;
  sc_time local_time = m_qk.get_local_time();
  payload.set_data_ptr((unsigned char *)&water_packet);

  payload.set_write();

  water_packet.waterLevel = waterLevelInput_rtl.read();
  initiator_socket->b_transport(payload, local_time);
}

void RTL_TO_TLM::invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range)
{}
tlm::tlm_sync_enum RTL_TO_TLM::nb_transport_bw(tlm::tlm_generic_payload &  trans, tlm::tlm_phase &  phase, sc_time &  t)
{
    return tlm::TLM_ACCEPTED;
}