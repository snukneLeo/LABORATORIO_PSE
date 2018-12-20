#include "dist_UT.hh"

dist_UT::dist_UT(sc_module_name name_)
  : sc_module(name_)
  , target_socket("target_socket")
  , pending_transaction(NULL)
{

  target_socket(*this);

}

void dist_UT::b_transport(tlm::tlm_generic_payload& trans, sc_time& t)
{
  cout<<"[DIST:] b_transport - ";
  
  ioDataStruct = *((iostruct*) trans.get_data_ptr());
  if (trans.is_write()) {
    cout<<"write"<<endl;
    dist_function();
    trans.set_response_status(tlm::TLM_OK_RESPONSE);
    *((iostruct*) trans.get_data_ptr()) = ioDataStruct;
  } 
  else if (trans.is_read()){
    cout<<"read"<<endl;
    ioDataStruct.result = sum;
    *((iostruct*) trans.get_data_ptr()) = ioDataStruct;
    sum = 0;
  }

}

bool dist_UT::get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmi_data)
{
  return false;
}

tlm::tlm_sync_enum dist_UT::nb_transport_fw(tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_time& t)
{
  return tlm::TLM_COMPLETED;
}

unsigned int dist_UT::transport_dbg(tlm::tlm_generic_payload& trans)
{
  return 0;
}



void dist_UT:: dist_function()
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

void dist_UT:: end_of_elaboration()
{

}

void dist_UT:: reset()
{

}
