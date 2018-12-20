#include "root_UT_testbench.hh"

void root_UT_testbench::invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range)
{
  
}

tlm::tlm_sync_enum root_UT_testbench::nb_transport_bw(tlm::tlm_generic_payload &  trans, tlm::tlm_phase &  phase, sc_time &  t)
{
  return tlm::TLM_COMPLETED;
}


void root_UT_testbench::run()
{

  sc_time local_time;
  iostruct root_packet;
  tlm::tlm_generic_payload payload;	

  // send one random number - write invocation
  root_packet.datain = (rand() % 256);
  cout<<"[TB:] Calculating the square root of "<<root_packet.datain<<endl;
  payload.set_data_ptr((unsigned char*) &root_packet); // set payload data
  payload.set_address(0); // set address, 0 here since we have only 1 target and 1 initiator 
  payload.set_write(); // write transaction

  cout<<"[TB:] Invoking the b_transport primitive - write"<<endl;
  initiator_socket->b_transport(payload, local_time); // invoke the transport primitive

  if(payload.get_response_status() == tlm::TLM_OK_RESPONSE){
    // check that the protocol has been correctly implemented
    // and print the result
    cout<<"[TB:] TLM protocol correctly implemented"<<endl;
    cout<<"[TB:] Result is: " << root_packet.result << endl;
  }
  sc_stop();
  
}

// constructor to initialize the TLM socket and the main thread
root_UT_testbench::root_UT_testbench(sc_module_name name)
  : sc_module(name)
{

  initiator_socket(*this);
  SC_THREAD(run);

}
