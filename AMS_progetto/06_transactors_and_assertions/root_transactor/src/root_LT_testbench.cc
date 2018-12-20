#include "root_LT_testbench.hh"

void root_LT_testbench::invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range)
{
  
}

tlm::tlm_sync_enum root_LT_testbench::nb_transport_bw(tlm::tlm_generic_payload &  trans, tlm::tlm_phase &  phase, sc_time &  t)
{
  cout<<sc_simulation_time()<<" - "<<name()<<" - nb_transport_bw"<<endl;
  return tlm::TLM_COMPLETED;
}

void root_LT_testbench::run()
{

  sc_time local_time = m_qk.get_local_time();

  // First transaction (initialization)
  iostruct root_packet;
  tlm::tlm_generic_payload payload;	

//  for (int i = 1; i <= 128; i++){
    cout<<sc_simulation_time()<<" - "<<name()<<" - run"<<endl;

    root_packet.datain = (rand() % 256);
    cout <<"The square root of : " << root_packet.datain << endl;
    payload.set_data_ptr((unsigned char*) &root_packet);
    payload.set_address(0);
    payload.set_write();
    
    local_time = m_qk.get_local_time();

    // start write transaction
    initiator_socket->b_transport(payload, local_time);

    // start read transaction
    payload.set_read();
    initiator_socket->b_transport(payload, local_time);
    if(payload.get_response_status() == tlm::TLM_OK_RESPONSE){
      cout<< "... is: " << root_packet.result << endl;
    }

    cout << "Time: " << sc_time_stamp() << " + " << local_time << endl;
    m_qk.set(local_time);
    if (m_qk.need_sync()) {
      cout << "SYNCHRONIZING" << endl;
      m_qk.sync();
      cout << "#####################" << endl;
    }
    
//  }
  sc_stop();
  
}

root_LT_testbench::root_LT_testbench(sc_module_name name)
  : sc_module(name)
{

  initiator_socket(*this);

  SC_THREAD(run);

  m_qk.set_global_quantum(sc_time(500, SC_NS));
  m_qk.reset();

}
