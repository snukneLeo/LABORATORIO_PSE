#include "div_AT4_testbench.hh"

void div_AT4_testbench::invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range)
{
  
}

tlm::tlm_sync_enum div_AT4_testbench::nb_transport_bw(tlm::tlm_generic_payload &  trans, tlm::tlm_phase &  phase, sc_time &  t)
{
  
  // There must be a pending response.
  if (!response_pending) {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
    return tlm::TLM_COMPLETED;
  }

  // The phase should be BEGIN_RESP.
  if (phase != tlm::BEGIN_RESP) {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
    return tlm::TLM_COMPLETED;
  }
  available_response.notify();
  phase = tlm::END_RESP;

  return tlm::TLM_COMPLETED;
}


void div_AT4_testbench::run()
{
  sc_time local_time = SC_ZERO_TIME;

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

    // start write transaction
    tlm::tlm_phase phase = tlm::BEGIN_REQ;
    tlm::tlm_generic_payload payload;
    payload.set_address(0);
    payload.set_data_ptr((unsigned char*) &div_packet);
    payload.set_write();

    tlm::tlm_sync_enum result = initiator_socket->nb_transport_fw(payload, phase, local_time);
    
    if (result == tlm::TLM_COMPLETED) {
  
      // If the target immediately completes the transaction something
      // wrong happened. We should inspect the response status and
      // take appropriate actions. In this case we just stop the simulation.
      sc_stop();
    }

    // Phase must be END_REQ
    if (phase != tlm::END_REQ) {

      sc_stop();
    }

    response_pending = true;
    wait(available_response);
    response_pending = false;

    // start read transaction
    phase = tlm::BEGIN_REQ;
    payload.set_address(0);
    payload.set_data_ptr((unsigned char*) &div_packet);
    payload.set_read();

    result = initiator_socket->nb_transport_fw(payload, phase, local_time);

    if (result == tlm::TLM_COMPLETED) {

      // If the target immediately completes the transaction something
      // wrong happened. We should inspect the response status and
      // take appropriate actions. In this case we just stop the simulation.
      sc_stop();
    }

    // Phase must be END_REQ
    if (phase != tlm::END_REQ) {

      sc_stop();
    }

    response_pending = true;
    wait(available_response);
    response_pending = false;    

    if(payload.get_response_status() == tlm::TLM_OK_RESPONSE){
      cout << "\tresult:\t" << div_packet.result << endl;
      cout<<endl;
    }
      
  }
  sc_stop();
    
}







div_AT4_testbench::div_AT4_testbench(sc_module_name name)
  : sc_module(name)
  , response_pending(false)
{

  initiator_socket(*this);

  SC_THREAD(run);

}
