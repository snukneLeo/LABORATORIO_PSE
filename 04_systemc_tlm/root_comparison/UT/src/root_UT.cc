#include "root_UT.hh"


root_UT::root_UT(sc_module_name name_)
  : sc_module(name_)
  , target_socket("target_socket")
  , pending_transaction(NULL)
{

  target_socket(*this);

}

void root_UT::b_transport(tlm::tlm_generic_payload& trans, sc_time& t)
{

  ioDataStruct = *((iostruct*) trans.get_data_ptr());

  if (trans.is_write()) {
    root_function();
    trans.set_response_status(tlm::TLM_OK_RESPONSE);
    ioDataStruct.result = tmp_result;
    *((iostruct*) trans.get_data_ptr()) = ioDataStruct;
  } 
  else if (trans.is_read()){
    ioDataStruct.result = tmp_result;
    *((iostruct*) trans.get_data_ptr()) = ioDataStruct;
  }

}

bool root_UT::get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmi_data)
{
  return false;
}

tlm::tlm_sync_enum root_UT::nb_transport_fw(tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_time& t)
{
  return tlm::TLM_COMPLETED;
}

unsigned int root_UT::transport_dbg(tlm::tlm_generic_payload& trans)
{
  return 0;
}



void root_UT:: root_function()
{
  tmp_result = sqrt((float)ioDataStruct.datain);
}

// Initialization:
void root_UT:: end_of_elaboration()
{

}

void root_UT:: reset()
{

}
