#include "root_LT.hh"

root_LT::root_LT(sc_module_name name_)
  : sc_module(name_)
  , target_socket("target_socket")
  , pending_transaction(NULL)
{
  target_socket(*this);
}

void root_LT::b_transport(tlm::tlm_generic_payload& trans, sc_time& t)
{

  timing_annotation = SC_ZERO_TIME;

  ioDataStruct = *((iostruct*) trans.get_data_ptr());

  if (trans.is_write()) {
    cout<<"\t\t[ROOT:] Received invocation of the b_transport primitive - write"<<endl;
    cout<<"\t\t[ROOT:] Invoking the root_function to calculate the square root"<<endl;
    root_function();
    ioDataStruct.result = tmp_result;
    cout<<"\t\t[ROOT:] Returning result: "<<tmp_result<<endl;
    *((iostruct*) trans.get_data_ptr()) = ioDataStruct;
    trans.set_response_status(tlm::TLM_OK_RESPONSE);
  } 
  else if (trans.is_read()){
    cout<<"\t\t[ROOT:] Received invocation of the b_transport primitive - read"<<endl;
    ioDataStruct.result = tmp_result;
    cout<<"\t\t[ROOT:] Returning result: "<<tmp_result<<endl;
    *((iostruct*) trans.get_data_ptr()) = ioDataStruct;
  }

  t += timing_annotation;

}

bool root_LT::get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmi_data)
{
  return false;
}

tlm::tlm_sync_enum root_LT::nb_transport_fw(tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_time& t)
{
  return tlm::TLM_COMPLETED;
}

unsigned int root_LT::transport_dbg(tlm::tlm_generic_payload& trans)
{
  return 0;
}

void root_LT:: root_function()
{
  cout<<"\t\t[ROOT:] Calculating root_function ... "<<endl;
  tmp_result = sqrt((float)ioDataStruct.datain);
  timing_annotation += sc_time(100, SC_NS);

}


// Initialization:
void root_LT::end_of_elaboration()
{

}

void root_LT::reset()
{

}
