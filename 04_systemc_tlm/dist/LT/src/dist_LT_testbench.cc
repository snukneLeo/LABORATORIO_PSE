#include "dist_LT_testbench.hh"

void dist_LT_testbench::invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range)
{
  
}

tlm::tlm_sync_enum dist_LT_testbench::nb_transport_bw(tlm::tlm_generic_payload &  trans, tlm::tlm_phase &  phase, sc_time &  t)
{
  return tlm::TLM_COMPLETED;
}

void dist_LT_testbench::run()
{

  sc_time local_time = m_qk.get_local_time();

  // First transaction (initialization)
  iostruct dist_packet;
  tlm::tlm_generic_payload payload;	

  cout<<"First check: comparing two random images. The DIST module will not "<<endl;
  cout<<"recognize them as photographs of the same person."<<endl;

  //PHASE 1: memorize the reference image
  for (int i = 1; i <= 128; i++){
    dist_packet.datain = (rand() % 256) << 24; 
    dist_packet.datain += (rand() % 256) << 16;  
    dist_packet.datain += (rand() % 256) << 8;
    dist_packet.datain += (rand() % 256);
    dist_packet.address = (i*4) - 4;
    dist_packet.mode = 1;
 
    payload.set_data_ptr((unsigned char*) &dist_packet);
    payload.set_address(0);
    payload.set_write();
    // start write transaction

    cout<<"[TB:] b_transport invocation"<<endl;
    initiator_socket->b_transport(payload, local_time);

    if(payload.get_response_status() != tlm::TLM_OK_RESPONSE){
      cout << "PROTOCOL ERROR!" << endl;
    }

    if (m_qk.need_sync()) {
      cout << "SYNCHRONIZING" << endl;
      m_qk.sync();
      cout << "#####################" << endl;
    }
  }

  //PHASE 2: compare with a new image
  for (int i = 1; i <= 128; i++){
    dist_packet.datain = (rand() % 256) << 24; 
    dist_packet.datain += (rand() % 256) << 16;  
    dist_packet.datain += (rand() % 256) << 8;
    dist_packet.datain += (rand() % 256);

    dist_packet.address = (i*4) - 4;
    dist_packet.mode = 0;
 
    payload.set_data_ptr((unsigned char*) &dist_packet);
    payload.set_address(0);
    payload.set_write();

    // start write transaction
    cout<<"[TB:] b_transport invocation"<<endl;
    initiator_socket->b_transport(payload, local_time);
  }
    // start read transaction
  payload.set_read();
  
  cout<<"[TB:] b_transport invocation"<<endl;
  initiator_socket->b_transport(payload, local_time);

  if(payload.get_response_status() == tlm::TLM_OK_RESPONSE){

  }
  if (m_qk.need_sync()) {
    cout << "SYNCHRONIZING" << endl;
    m_qk.sync();
    cout << "#####################" << endl;
  }
  
  if (sqrt((float)dist_packet.result) < THRESHOLD){

    //the two images represent the same person
    cout<<"RECOGNIZED: the two images represent the same person"<<endl;
    cout<<"            access allowed!"<<endl;
    cout<<endl;
  }

  else{

    //the two images represent two different persons
    cout<<"WRONG IMAGE: the two images represent two different persons"<<endl;
    cout<<"            access forbidden!"<<endl;
    cout<<endl;
  }
    
  cout<<"Second check: comparing two identical images, with only few errors."<<endl;
  cout<<"The DIST module will recognize them as photographs of the same person."<<endl;

  unsigned int a [512];
    
  //PHASE 1: memorize the reference image
  for (int i = 1; i <= 128; i++){

    //generate random pixel ARGB component
    a[i*4-4] = (rand() % 256); 
    a[i*4-3] = (rand() % 256); 
    a[i*4-2] = (rand() % 256); 
    a[i*4-1] = (rand() % 256); 

    dist_packet.datain = a[i*4-4] << 24; 
    dist_packet.datain += a[i*4-3] << 16;  
    dist_packet.datain += a[i*4-2] << 8;
    dist_packet.datain += a[i*4-1];
    
    dist_packet.address = (i*4) - 4;
    dist_packet.mode = 1;
    
    payload.set_data_ptr((unsigned char*) &dist_packet);
    payload.set_address(0);
    payload.set_write();
  }

  // start write transaction
  cout<<"[TB:] b_transport invocation"<<endl;
  initiator_socket->b_transport(payload, local_time);

  if(payload.get_response_status() != tlm::TLM_OK_RESPONSE){
    cout << "PROTOCOL ERROR!" << endl;
  }
    
  if (m_qk.need_sync()) {
    cout << "SYNCHRONIZING" << endl;
    m_qk.sync();
    cout << "#####################" << endl;
  }
  

  //PHASE 2: compare with a new image

  for (int i = 1; i <= 128; i++){

    
    if ((i%10) == 0){ 
      //inject some errors in the previously generated image
      dist_packet.datain = 0;
    }
    
    else {
      dist_packet.datain = a[i*4-4] << 24; 
      dist_packet.datain += a[i*4-3] << 16;  
      dist_packet.datain += a[i*4-2] << 8;
      dist_packet.datain += a[i*4-1];
    }
    dist_packet.address = (i*4) - 4;
    dist_packet.mode = 0;
  
    payload.set_data_ptr((unsigned char*) &dist_packet);
    payload.set_address(0);
    payload.set_write();
    // start write transaction
    
    cout<<"[TB:] b_transport invocation"<<endl;
    initiator_socket->b_transport(payload, local_time);

    // start read transaction
    payload.set_read();
    cout<<"[TB:] b_transport invocation"<<endl;
    initiator_socket->b_transport(payload, local_time);
    if(payload.get_response_status() == tlm::TLM_OK_RESPONSE){
    }
    if (m_qk.need_sync()) {
      cout << "SYNCHRONIZING" << endl;
      m_qk.sync();
      cout << "#####################" << endl;
    }
  }
  
  if (sqrt((float)dist_packet.result) < THRESHOLD){

    //the two images represent the same person
    cout<<"RECOGNIZED: the two images represent the same person"<<endl;
    cout<<"            access allowed!"<<endl;
    cout<<endl;
  }
  else{

    //the two images represent two different persons
    cout<<"WRONG IMAGE: the two images represent two different persons"<<endl;
    cout<<"            access forbidden!"<<endl;
    cout<<endl;
  }
 
  
  sc_stop();
  
}





dist_LT_testbench::dist_LT_testbench(sc_module_name name)
  : sc_module(name)
{

  initiator_socket(*this);

  SC_THREAD(run);

  m_qk.set_global_quantum(sc_time(500, SC_NS));
  m_qk.reset();

}
