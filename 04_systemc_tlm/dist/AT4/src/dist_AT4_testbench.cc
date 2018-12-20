#include "dist_AT4_testbench.hh"

void dist_AT4_testbench::invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range)
{
  
}

tlm::tlm_sync_enum dist_AT4_testbench::nb_transport_bw(tlm::tlm_generic_payload &  trans, tlm::tlm_phase &  phase, sc_time &  t)
{
 
  cout<<"[TB:] nb_transport_bw - phase END RESP"<<endl;
  // There must be a pending response.
  if (!response_pending) {
    cout << "Unexpected state" << endl;
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
    return tlm::TLM_COMPLETED;
  }

  // The phase should be BEGIN_RESP.
  if (phase != tlm::BEGIN_RESP) {
    cout << "Unexpected phase" << endl;
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
    return tlm::TLM_COMPLETED;
  }

  available_response.notify();
  phase = tlm::END_RESP;

  return tlm::TLM_COMPLETED;
}

void dist_AT4_testbench::run()
{
  tlm::tlm_sync_enum result;
  sc_time local_time = SC_ZERO_TIME;

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
    
    // start write transaction
    tlm::tlm_phase phase = tlm::BEGIN_REQ;
    tlm::tlm_generic_payload payload;

    payload.set_address(0);
    payload.set_data_ptr((unsigned char*) &dist_packet);
    payload.set_write();

    cout<<"[TB:] nb_transport_fw invocation - phase BEGIN REQ"<<endl;
    result = initiator_socket->nb_transport_fw(payload, phase, local_time);

    if (result == tlm::TLM_COMPLETED) {

      // If the target immediately completes the transaction something
      // wrong happened. We should inspect the response status and
      // take appropriate actions. In this case we just stop the simulation.
      cout << "Transaction error. Forcing simulation stop." << endl;
      sc_stop();
    }

    // Phase must be END_REQ
    if (phase != tlm::END_REQ) {

      cout << "Unexpected protocol phase. Forcing simulation stop." << endl;
      sc_stop();
    }
  
    response_pending = true;
    wait(available_response);
    response_pending = false;
  }
  
  //PHASE 2: compare with a new image
  for (int i = 1; i <= 128; i++){
    dist_packet.datain = (rand() % 256) << 24; 
    dist_packet.datain += (rand() % 256) << 16;  
    dist_packet.datain += (rand() % 256) << 8;
    dist_packet.datain += (rand() % 256);
    dist_packet.address = (i*4) - 4;
    dist_packet.mode = 0;
    
    // start write transaction
    tlm::tlm_phase phase = tlm::BEGIN_REQ;
    tlm::tlm_generic_payload payload;

    payload.set_address(0);
    payload.set_data_ptr((unsigned char*) &dist_packet);
    payload.set_write();

    cout<<"[TB:] nb_transport_fw invocation - phase BEGIN REQ"<<endl;
    result = initiator_socket->nb_transport_fw(payload, phase, local_time);

    if (result == tlm::TLM_COMPLETED) {

      // If the target immediately completes the transaction something
      // wrong happened. We should inspect the response status and
      // take appropriate actions. In this case we just stop the simulation.
      cout << "Transaction error. Forcing simulation stop." << endl;
      sc_stop();
    }

    // Phase must be END_REQ
    if (phase != tlm::END_REQ) {

      cout << "Unexpected protocol phase. Forcing simulation stop." << endl;
      sc_stop();
    }

    response_pending = true;
    wait(available_response);
    response_pending = false;
  }   
  
  // start read transaction
  tlm::tlm_phase phase = tlm::BEGIN_REQ;
  phase = tlm::BEGIN_REQ;
  payload.set_address(0);
  payload.set_data_ptr((unsigned char*) &dist_packet);
  payload.set_read();

  cout<<"[TB:] nb_transport_fw invocation - phase BEGIN REQ"<<endl;
  result = initiator_socket->nb_transport_fw(payload, phase, local_time);

  if (result == tlm::TLM_COMPLETED) {

    // If the target immediately completes the transaction something
    // wrong happened. We should inspect the response status and
    // take appropriate actions. In this case we just stop the simulation.
    cout << "Transaction error. Forcing simulation stop." << endl;
    sc_stop();
  }

  // Phase must be END_REQ
  if (phase != tlm::END_REQ) {

    cout << "Unexpected protocol phase. Forcing simulation stop." << endl;
    sc_stop();
  }

  response_pending = true;
  wait(available_response);
  response_pending = false;    

  if(payload.get_response_status() == tlm::TLM_OK_RESPONSE){
//    cout << "\t is: " << dist_packet.result << endl;
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
    
    // start write transaction
    tlm::tlm_phase phase = tlm::BEGIN_REQ;
    tlm::tlm_generic_payload payload;

    payload.set_address(0);
    payload.set_data_ptr((unsigned char*) &dist_packet);
    payload.set_write();

    cout<<"[TB:] nb_transport_fw invocation - phase BEGIN REQ"<<endl;
    result = initiator_socket->nb_transport_fw(payload, phase, local_time);

    if (result == tlm::TLM_COMPLETED) {

      // If the target immediately completes the transaction something
      // wrong happened. We should inspect the response status and
      // take appropriate actions. In this case we just stop the simulation.
      cout << "Transaction error. Forcing simulation stop." << endl;
      sc_stop();
    }

    // Phase must be END_REQ
    if (phase != tlm::END_REQ) {

      cout << "Unexpected protocol phase. Forcing simulation stop." << endl;
      sc_stop();
    }
  
    response_pending = true;
    wait(available_response);
    response_pending = false;
  }
  //PHASE 2: compare with a new image
  for (int i = 1; i <= 128; i++){

    if ((i%100) == 0){ 
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
    
    // start write transaction
    tlm::tlm_phase phase = tlm::BEGIN_REQ;
    tlm::tlm_generic_payload payload;

    payload.set_address(0);
    payload.set_data_ptr((unsigned char*) &dist_packet);
    payload.set_write();

    cout<<"[TB:] nb_transport_fw invocation - phase BEGIN REQ"<<endl;
    result = initiator_socket->nb_transport_fw(payload, phase, local_time);

    if (result == tlm::TLM_COMPLETED) {

      // If the target immediately completes the transaction something
      // wrong happened. We should inspect the response status and
      // take appropriate actions. In this case we just stop the simulation.
      cout << "Transaction error. Forcing simulation stop." << endl;
      sc_stop();
    }

    // Phase must be END_REQ
    if (phase != tlm::END_REQ) {

      cout << "Unexpected protocol phase. Forcing simulation stop." << endl;
      sc_stop();
    }

    response_pending = true;
    wait(available_response);
    response_pending = false;
  }   

  // start read transaction
  phase = tlm::BEGIN_REQ;
  payload.set_address(0);
  payload.set_data_ptr((unsigned char*) &dist_packet);
  payload.set_read();

  cout<<"[TB:] nb_transport_fw invocation - phase BEGIN REQ"<<endl;
  result = initiator_socket->nb_transport_fw(payload, phase, local_time);

  if (result == tlm::TLM_COMPLETED) {

    // If the target immediately completes the transaction something
    // wrong happened. We should inspect the response status and
    // take appropriate actions. In this case we just stop the simulation.
    cout << "Transaction error. Forcing simulation stop." << endl;
    sc_stop();
  }

  // Phase must be END_REQ
  if (phase != tlm::END_REQ) {
    cout << "Unexpected protocol phase. Forcing simulation stop." << endl;
    sc_stop();
  }

  response_pending = true;
  wait(available_response);
  response_pending = false;    

  if(payload.get_response_status() == tlm::TLM_OK_RESPONSE){
//    cout << "\t is: " << dist_packet.result << endl;
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

dist_AT4_testbench::dist_AT4_testbench(sc_module_name name)
  : sc_module(name)
  , response_pending(false)
{

  initiator_socket(*this);

  SC_THREAD(run);

}
