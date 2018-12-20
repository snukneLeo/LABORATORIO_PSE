#include "root_AT4_testbench.hh"

// initiator process
void root_AT4_testbench::run()
{
  sc_time local_time = SC_ZERO_TIME;
  iostruct root_packet;
  tlm::tlm_generic_payload payload;	

  // send one random number - write invocation
  root_packet.datain = (rand() % 256);
  cout<<"[TB:] Calculating the square root of "<<root_packet.datain<<endl;
  
  // set phase: begin request
  tlm::tlm_phase phase = tlm::BEGIN_REQ;
  
  // update payload
  payload.set_address(0);
  payload.set_data_ptr((unsigned char*) &root_packet);
  payload.set_write();

  cout<<"[TB:] Invoking the nb_transport_fw primitive of root - write"<<endl;
  tlm::tlm_sync_enum result = initiator_socket->nb_transport_fw(payload, phase, local_time);  // invoke the transport primitive
                                                                                              // pass also the phase

  if (result == tlm::TLM_COMPLETED) {
    // If the target immediately completes the transaction something
    // wrong happened. We should inspect the response status and
    // take appropriate actions. In this case we just stop the simulation.
    cout << "[ERROR:] Transaction error on nb_transport_fw. Forcing simulation stop." << endl;
    sc_stop();
  }

  // Phase must be an end request, used by the target to notify that
  // it accepted the request
  // else, there is something wrong in the protocol
  if (phase != tlm::END_REQ) {
    cout << "[ERROR: ] Unexpected protocol phase on nb_transport_fw. Forcing simulation stop." << endl;
    sc_stop();
  }

  cout<<"[TB:] Waiting for nb_transport_bw to be invoked "<<endl;
  response_pending = true; // we have one request pending
  wait(available_response); // thus we suspend until the protocol is finished
  
  // if I am here, then the target has invoked the backward primitive and the AT4 protocol is finished
  // I can issue a new request to get the result
  response_pending = false;

  phase = tlm::BEGIN_REQ;
  payload.set_address(0);
  payload.set_data_ptr((unsigned char*) &root_packet);
  payload.set_read();
  
  cout<<"[TB:] Invoking the nb_transport_fw primitive of root - read"<<endl;
  result = initiator_socket->nb_transport_fw(payload, phase, local_time);

  if (result == tlm::TLM_COMPLETED) {
    cout << "[ERROR:] Transaction error on nb_transport_fw. Forcing simulation stop." << endl;
    sc_stop();
  }

  if (phase != tlm::END_REQ) {
    cout << "[ERROR: ] Unexpected protocol phase on nb_transport_fw. Forcing simulation stop." << endl;
    sc_stop();
  }

  cout<<"[TB:] Waiting for nb_transport_bw to be invoked "<<endl;
  response_pending = true;
  wait(available_response);

  // if I am here, then the target has invoked the backward primitive and the AT4 protocol is finished
  // I can get the final result and print it
  response_pending = false;    

  if(payload.get_response_status() == tlm::TLM_OK_RESPONSE){
    cout<<"[TB:] TLM protocol correctly implemented"<<endl;
    cout<<"[TB:] Result is: " << root_packet.result << endl;
  }
 
  sc_stop();
}


tlm::tlm_sync_enum root_AT4_testbench::nb_transport_bw(tlm::tlm_generic_payload &  trans, tlm::tlm_phase &  phase, sc_time &  t)
{
  
  // If response_pending is true, then the initiator had made a request to the target
  // and this invocation is the answer
  if (!response_pending) {
    cout << "[ERROR:] Unexpected state for nb_transport_be" << endl;
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
    return tlm::TLM_COMPLETED;
  }
  
  // The phase of the invocation must be begin response, or there is some error in the protocol
  if (phase != tlm::BEGIN_RESP) {
    cout << "[ERROR:] Unexpected phase for nb_transport_be" << endl;
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
    return tlm::TLM_COMPLETED;
  }

  // reactivate the initiator process to go on with computation
  available_response.notify();
  
  // phase is updated to end response since the AT4 protocol is finished
  phase = tlm::END_RESP;
  
  return tlm::TLM_COMPLETED;
}


// constructor
// initialize TLM socket and state that run is a thread
root_AT4_testbench::root_AT4_testbench(sc_module_name name)
  : sc_module(name)
  , response_pending(false)
{

  initiator_socket(*this);

  SC_THREAD(run);

}


// necessary to be compliant with the standard
// not used here
void root_AT4_testbench::invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range)
{
  
}
