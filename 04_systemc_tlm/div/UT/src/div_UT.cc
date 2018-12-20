#include "div_UT.hh"

div_UT::div_UT(sc_module_name name_)
  : sc_module(name_)
  , target_socket("target_socket")
  , pending_transaction(NULL)
{

  target_socket(*this);

}

void div_UT::b_transport(tlm::tlm_generic_payload& trans, sc_time& t)
{
  ioDataStruct = *((iostruct*) trans.get_data_ptr());

  if (trans.is_write()) {
    div_function();
    trans.set_response_status(tlm::TLM_OK_RESPONSE);
    *((iostruct*) trans.get_data_ptr()) = ioDataStruct;
  } 
  else if (trans.is_read()){
    ioDataStruct.result = tmp_result;
    *((iostruct*) trans.get_data_ptr()) = ioDataStruct;
  }

}

bool div_UT::get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmi_data)
{
  return false;
}

tlm::tlm_sync_enum div_UT::nb_transport_fw(tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_time& t)
{
  return tlm::TLM_COMPLETED;
}

unsigned int div_UT::transport_dbg(tlm::tlm_generic_payload& trans)
{
  return 0;
}


void div_UT:: div_function()
{
  unsigned int R;
  unsigned int G;
  unsigned int B;
  unsigned int r;
  unsigned int g;
  int sum =0;
   
  int tmp;
  tmp = ioDataStruct.datain;
  
  //dispach of data
  B = (tmp & 0x000000ff);
  G = (tmp & 0x0000ff00) >> 8;
  R = (tmp & 0x00ff0000) >> 16;

  //evaluate
  sum = R + G + B;
  r = (R << 10) / sum;
  g = (G << 10) / sum;

  //build result
  tmp_result = (((r & 0x0000ffff) << 16) | (g & 0x0000ffff));
}


// Initialization:
void div_UT:: end_of_elaboration()
{

}

void div_UT:: reset()
{

}
