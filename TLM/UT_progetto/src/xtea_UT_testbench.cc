#include "xtea_UT_testbench.hh"

void xtea_UT_testbench::invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range)
{
  
}

tlm::tlm_sync_enum xtea_UT_testbench::nb_transport_bw(tlm::tlm_generic_payload &  trans, tlm::tlm_phase &  phase, sc_time &  t)
{
  return tlm::TLM_COMPLETED;
}


void xtea_UT_testbench::run()
{

  sc_time local_time;
  iostruct xtea_packet;
  tlm::tlm_generic_payload payload;	

  // send one random number - write invocation
  payload.set_data_ptr((unsigned char*) &xtea_packet); // set payload data
  payload.set_address(0); // set address, 0 here since we have only 1 target and 1 initiator 
  payload.set_write(); // write transaction


  ///////////////////////////////////////////////////////////////////////////////////////////////////////
  xtea_packet.mode = 0;
  xtea_packet.word0 = 0x12345678; 
  xtea_packet.word1 = 0x9abcdeff; 
  xtea_packet.key0 = 0x6a1d78c8; 
  xtea_packet.key1 = 0x8c86d67f; 
  xtea_packet.key2 = 0x2a65bfbe; 
  xtea_packet.key3 = 0xb4bd6e46;

  cout << "Original text: " << hex << xtea_packet.word0 << "," << hex << xtea_packet.word1 << "\n";

  // start write transaction
  initiator_socket->b_transport(payload, local_time);
  cout << "Encrypted text: " << hex << xtea_packet.result0 << "," << hex << xtea_packet.result1 << "\n";

  xtea_packet.mode = 1;
  // start read transaction
  payload.set_read();
  
  initiator_socket->b_transport(payload, local_time);
  if (payload.get_response_status() == tlm::TLM_OK_RESPONSE) {
    cout << "Decrypted text: " << hex << xtea_packet.result0 << "," << hex << xtea_packet.result1 << "\n";
  }

  sc_stop();
  
}

// constructor to initialize the TLM socket and the main thread
xtea_UT_testbench::xtea_UT_testbench(sc_module_name name)
  : sc_module(name)
{

  initiator_socket(*this);
  SC_THREAD(run);

}
