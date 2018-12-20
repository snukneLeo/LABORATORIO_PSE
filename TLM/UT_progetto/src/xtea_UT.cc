#include "xtea_UT.hh"

// constructor
// initialize the TLM socket
// no process, target works with function invocations from the initiator
xtea_UT::xtea_UT(sc_module_name name_)
  : sc_module(name_)
  , target_socket("target_socket")
  , pending_transaction(NULL)
  {
  target_socket(*this);
}

void xtea_UT::b_transport(tlm::tlm_generic_payload& trans, sc_time& t)
{
  // function invoked by the initiator
  
  // download data from the payload
  ioDataStruct = *((iostruct*) trans.get_data_ptr()); //faccio una coppia locale della mia struttura

  if (trans.is_write()) 
  { 
    //ENCRYPT
    xtea_function();
    ioDataStruct.result0 = tmp_result0;
    ioDataStruct.result1 = tmp_result1;
    trans.set_response_status(tlm::TLM_OK_RESPONSE);
    *((iostruct *) trans.get_data_ptr()) = ioDataStruct;
  } 
  else if (trans.is_read())
  { 
    //DECRYPT
    xtea_function();
    ioDataStruct.result0 = tmp_result0;
    ioDataStruct.result1 = tmp_result1;
    *((iostruct *) trans.get_data_ptr()) = ioDataStruct;
  }

}

void xtea_UT::xtea_function() {
  sc_uint<64> sum;
  sc_uint<32> i, delta, v0, v1, temp;
  sum = 0;
  tmp_result0 = 0;
  tmp_result1 = 0;

  if (ioDataStruct.mode == 0) 
  {
    v0 = ioDataStruct.word0;
    v1 = ioDataStruct.word1;
    // encipher
    delta = 0x9e3779b9;
    for (i = 0; i < 32; i++) {

      if ((sum & 3) == 0)
        temp = ioDataStruct.key0;
      else if ((sum & 3) == 1)
        temp = ioDataStruct.key1;
      else if ((sum & 3) == 2)
        temp = ioDataStruct.key2;
      else
        temp = ioDataStruct.key3;

      v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + temp);

      sum += delta;

      if (((sum >> 11) & 3) == 0)
        temp = ioDataStruct.key0;
      else if (((sum >> 11) & 3) == 1)
        temp = ioDataStruct.key1;
      else if (((sum >> 11) & 3) == 2)
        temp = ioDataStruct.key2;
      else
        temp = ioDataStruct.key3;

      v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + temp);
    }
  } else if (ioDataStruct.mode == 1) {
    // decipher
    delta = 0x9e3779b9;
    sum = delta * 32;
    v0 = ioDataStruct.result0;
    v1 = ioDataStruct.result1;
    for (i = 0; i < 32; i++) 
    {
      if (((sum >> 11) & 3) == 0)
        temp = ioDataStruct.key0;
      else if (((sum >> 11) & 3) == 1)
        temp = ioDataStruct.key1;
      else if (((sum >> 11) & 3) == 2)
        temp = ioDataStruct.key2;
      else
        temp = ioDataStruct.key3;

      v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + temp);

      sum -= delta;

      if ((sum & 3) == 0)
        temp = ioDataStruct.key0;
      else if ((sum & 3) == 1)
        temp = ioDataStruct.key1;
      else if ((sum & 3) == 2)
        temp = ioDataStruct.key2;
      else
        temp = ioDataStruct.key3;

      v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + temp);
    }
  }
  tmp_result0 = v0;
  tmp_result1 = v1;
}



// must be implemented to be compliant with the interface
// not significant in this code

bool xtea_UT::get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmi_data)
{
  return false;
}

tlm::tlm_sync_enum xtea_UT::nb_transport_fw(tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_time& t)
{
  return tlm::TLM_COMPLETED;
}

unsigned int xtea_UT::transport_dbg(tlm::tlm_generic_payload& trans)
{
  return 0;
}
