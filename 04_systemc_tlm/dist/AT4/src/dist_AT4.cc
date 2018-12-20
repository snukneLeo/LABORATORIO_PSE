#include "dist_AT4.hh"

dist_AT4::dist_AT4(sc_module_name name_)
  : sc_module(name_)
  , target_socket("target_socket")
  , pending_transaction(NULL)
{

  target_socket(*this);

  SC_THREAD(IOPROCESS);

}

void dist_AT4::b_transport(tlm::tlm_generic_payload& trans, sc_time& t)
{

}

bool dist_AT4::get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmi_data)
{
  return false;
}


tlm::tlm_sync_enum dist_AT4::nb_transport_fw(tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_time& t)
{

  cout<<"[DIST:] nb_transport_fw - phase END REQ"<<endl;

  // If there is already a pending transaction, we refuse to
  // serve the request (note that when we return TLM_COMPLETED
  // we do not need to update the phase).
  if (pending_transaction != NULL) {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
    return tlm::TLM_COMPLETED;
  }

  // Phase must be BEGIN_REQ, otherwise we set an
  // error response and complete the transaction.
  if (phase != tlm::BEGIN_REQ) {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
    return tlm::TLM_COMPLETED;
  }

  pending_transaction = &trans;
  ioDataStruct = *((iostruct*) trans.get_data_ptr());
  phase = tlm::END_REQ;
  io_event.notify();
  return tlm::TLM_UPDATED;
  
}

unsigned int dist_AT4::transport_dbg(tlm::tlm_generic_payload& trans)
{
  return 0;
}

void dist_AT4::IOPROCESS()
{

  sc_time timing_annotation;

  while (true) {
    wait(io_event);

    // When an io_event is notified, it means we must send the response back
    // to the initiator. We wait 100ns to model the delay required to
    // process the request.

    wait(100, SC_NS);    

    if (pending_transaction->is_write()) {
      dist_function();
    }
    
    else if (pending_transaction->is_read()){
      ioDataStruct.result = sum;
      sum = 0;      
    }

    pending_transaction->set_response_status(tlm::TLM_OK_RESPONSE);
    *((iostruct*) pending_transaction->get_data_ptr()) = ioDataStruct;
    tlm::tlm_phase phase = tlm::BEGIN_RESP;
    
    cout<<"[DIST:] nb_transport_bw invocation - phase BEGIN RESP"<<endl;
    target_socket->nb_transport_bw(*pending_transaction, phase, timing_annotation);
    pending_transaction = NULL;
  }
}


void dist_AT4:: dist_function()
{
  cout<<"[DIST:] dist_function - ";
  
  bool mode = ioDataStruct.mode;
  address = ioDataStruct.address;
  unsigned int tmp = 0;
  volatile unsigned int tmp1, tmp2, tmp3, tmp4;
  tmp = ioDataStruct.datain; 
  
  switch (mode) {
  
   case WRITE_MODE:
    cout<<"write mode"<<endl;
    volatile unsigned int middleres1, middleres2, middleres3, middleres4;
    volatile unsigned int p1, p2, p3, p4;
    tmp1 = (unsigned int)((tmp & 0x000000ff));
    tmp2 = (unsigned int)((tmp & 0x0000ff00) >> 8);
    tmp3 = (unsigned int)((tmp & 0x00ff0000) >> 16);
    tmp4 = (unsigned int)((tmp & 0xff000000) >> 24);

    middleres1 = tmp4 - image_segment[address];
    address++;
    middleres2 = tmp3 - image_segment[address];
    address++;
    middleres3 = tmp2 - image_segment[address];
    address++;
    middleres4 = tmp1 - image_segment[address];
    address++;

    p1 = middleres1 * middleres1;
    p2 = middleres2 * middleres2;
    p3 = middleres3 * middleres3;
    p4 = middleres4 * middleres4;
    sum += (p1 + p2 + p3 + p4);
    break; 
    
  case DB_MODE:
    cout<<"db mode"<<endl;
    tmp1 = (unsigned int)((tmp & 0x000000ff));
    tmp2 = (unsigned int)((tmp & 0x0000ff00) >> 8);
    tmp3 = (unsigned int)((tmp & 0x00ff0000) >> 16);
    tmp4 = (unsigned int)((tmp & 0xff000000) >> 24);
    cont_is = address;

    if (cont_is >= 512) cont_is = 0;

    image_segment[cont_is] = tmp4;
    cont_is++;
    image_segment[cont_is] = tmp3;
    cont_is++;
    image_segment[cont_is] = tmp2;
    cont_is++;
    image_segment[cont_is] = tmp1;
    cont_is++;
    break; 
  default :
  break; 
   };
}

void dist_AT4:: end_of_elaboration()
{

}

void dist_AT4:: reset()
{

}
