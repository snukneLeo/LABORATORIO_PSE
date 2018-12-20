#include "div_UT_testbench.hh"

void div_UT_testbench::invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range)
{
  
}

tlm::tlm_sync_enum div_UT_testbench::nb_transport_bw(tlm::tlm_generic_payload &  trans, tlm::tlm_phase &  phase, sc_time &  t)
{
  return tlm::TLM_COMPLETED;
}


void div_UT_testbench::run()
{

  sc_time local_time;
  // First transaction (initialization)
  iostruct div_packet;
  tlm::tlm_generic_payload payload;	

  cout<<"Calculate the div function of up to 128 pixels!"<<endl;

  
  for (int i = 1; i <= 128; i++){
    div_packet.datain = (rand() % 256) << 24; 
    div_packet.datain += (rand() % 256) << 16;  
    div_packet.datain += (rand() % 256) << 8;
    div_packet.datain += (rand() % 256);
    cout << "\tpixel:\t" << div_packet.datain << endl;
    
    payload.set_data_ptr((unsigned char*) &div_packet);
    payload.set_address(0);
    payload.set_write();

    // start write transaction
    initiator_socket->b_transport(payload, local_time);


    // start read transaction
    payload.set_read();

    initiator_socket->b_transport(payload, local_time);
    if(payload.get_response_status() == tlm::TLM_OK_RESPONSE){
      cout << "\tresult:\t" << div_packet.result << endl;
      cout<<endl;
    }

  }
  sc_stop();
  
}





div_UT_testbench::div_UT_testbench(sc_module_name name)
  : sc_module(name)
{

  initiator_socket(*this);

  SC_THREAD(run);

}
