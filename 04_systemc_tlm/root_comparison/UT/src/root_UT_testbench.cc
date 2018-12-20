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
  // First transaction (initialization)
  iostruct root_packet;
  tlm::tlm_generic_payload payload;	

  //cout<<"Calculate the square root of 10000000  numbers!"<<endl;

  for (int i = 1; i <= 10000000; i++){
    root_packet.datain = (rand() % 256);
    //cout<<"\tThe square root of "<<root_packet.datain;
    payload.set_data_ptr((unsigned char*) &root_packet);
    payload.set_address(0);
    payload.set_write();
    
    // start write transaction
    initiator_socket->b_transport(payload, local_time);

    // start read transaction
    if(payload.get_response_status() == tlm::TLM_OK_RESPONSE){
      //cout << "\t is: " << root_packet.result << endl;
    }

  }
  sc_stop();
  
}


root_UT_testbench::root_UT_testbench(sc_module_name name)
  : sc_module(name)
{

  initiator_socket(*this);

  SC_THREAD(run);

}
