#include "xtea_LT_testbench.hh"

void xtea_LT_testbench::run()
{
  cout<<sc_simulation_time()<<" - "<<name()<<" - run"<<endl;
  sc_time local_time = m_qk.get_local_time();

  iostruct xtea_packet;
  tlm::tlm_generic_payload payload;	

  // send one random number - write invocation
  payload.set_data_ptr((unsigned char*) &xtea_packet);
  payload.set_address(0);
  payload.set_write();


  xtea_packet.mode = 0;
  xtea_packet.word0 = 0x12345678; 
  xtea_packet.word1 = 0x9abcdeff; 
  xtea_packet.key0 = 0x6a1d78c8; 
  xtea_packet.key1 = 0x8c86d67f; 
  xtea_packet.key2 = 0x2a65bfbe; 
  xtea_packet.key3 = 0xb4bd6e46;
  // update the local time variable to send it to the target
  local_time = m_qk.get_local_time();


  cout << "Original text: " << hex << xtea_packet.word0 << "," << hex << xtea_packet.word1 << "\n";                        
  initiator_socket->b_transport(payload, local_time); // invoke the transport primitive
  
  if(payload.get_response_status() == tlm::TLM_OK_RESPONSE)
  {
    // check that the protocol has been correctly implemented
    // and print the result
    cout << "Encrypted text: " << hex << xtea_packet.result0 << "," << hex << xtea_packet.result1 << "\n";
  }

  xtea_packet.mode = 1;
  // start read transaction
  payload.set_read();
  
  initiator_socket->b_transport(payload, local_time);
  if (payload.get_response_status() == tlm::TLM_OK_RESPONSE) {
    cout << "Decrypted text: " << hex << xtea_packet.result0 << "," << hex << xtea_packet.result1 << "\n";
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
xtea_LT_testbench::xtea_LT_testbench(sc_module_name name)
  : sc_module(name)
{

  // initialize TLM socket
  initiator_socket(*this);

  // run is a thread
  SC_THREAD(run);

  // set parameters for temporal decoupling
  // one quantum is made of 500 ns
  m_qk.set_global_quantum(sc_time(200, SC_NS));
  m_qk.reset();

}




// necessary to be compliant with the standard but not used here
void xtea_LT_testbench::invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range)
{
  
}

tlm::tlm_sync_enum xtea_LT_testbench::nb_transport_bw(tlm::tlm_generic_payload &  trans, tlm::tlm_phase &  phase, sc_time &  t)
{
  return tlm::TLM_COMPLETED;
}
