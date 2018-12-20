#include "root_LT_testbench.hh"

void root_LT_testbench::run()
{
  cout<<sc_simulation_time()<<" - "<<name()<<" - run"<<endl;
  sc_time local_time = m_qk.get_local_time();

  iostruct root_packet;
  tlm::tlm_generic_payload payload;	

  // send one random number - write invocation
  root_packet.datain = (rand() % 256);
  cout<<"[TB:] Calculating the square root of "<<root_packet.datain<<endl;
  payload.set_data_ptr((unsigned char*) &root_packet);
  payload.set_address(0);
  payload.set_write();
  
  // update the local time variable to send it to the target
  local_time = m_qk.get_local_time();

  cout<<"[TB:] Invoking the b_transport primitive - write"<<endl;                         
  initiator_socket->b_transport(payload, local_time); // invoke the transport primitive
  
    if(payload.get_response_status() == tlm::TLM_OK_RESPONSE){
      // check that the protocol has been correctly implemented
      // and print the result
      cout<<"[TB:] TLM protocol correctly implemented"<<endl;
      cout<<"[TB:] Result is: " << root_packet.result << endl;
  }

  // temporal decoupling> get time and check if we have to synchronize with the target 
  cout << "Time: " << sc_time_stamp() << " + " << local_time << endl;
  m_qk.set(local_time);
  if (m_qk.need_sync()) {
    // synchronize simulation time
    cout << "SYNCHRONIZING" << endl;
    m_qk.sync();
    cout << "#####################" << endl;
  }
  sc_stop();
  
}


// constructor
root_LT_testbench::root_LT_testbench(sc_module_name name)
  : sc_module(name)
{

  // initialize TLM socket
  initiator_socket(*this);

  // run is a thread
  SC_THREAD(run);

  // set parameters for temporal decoupling
  // one quantum is made of 500 ns
  m_qk.set_global_quantum(sc_time(500, SC_NS));
  m_qk.reset();

}




// necessary to be compliant with the standard but not used here
void root_LT_testbench::invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range)
{
  
}

tlm::tlm_sync_enum root_LT_testbench::nb_transport_bw(tlm::tlm_generic_payload &  trans, tlm::tlm_phase &  phase, sc_time &  t)
{
  return tlm::TLM_COMPLETED;
}
