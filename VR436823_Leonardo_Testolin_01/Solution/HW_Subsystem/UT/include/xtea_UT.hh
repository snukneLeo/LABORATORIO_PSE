#ifndef __xtea_UT_HPP__
#define __xtea_UT_HPP__

#include <systemc.h>
#include <tlm.h>
#include "define_UT.hh"

class xtea_UT
  : public sc_module
  , public virtual tlm::tlm_fw_transport_if<>
{

 public:

  // TLM target
  tlm::tlm_target_socket<> target_socket;

  // b_transport invocata dal initiator per chiamare il target
  virtual void b_transport(tlm::tlm_generic_payload& trans, sc_time& t);

  //funzioni definite in quanto la classe richiede questi metodi
  virtual bool get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmi_data);
  virtual tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_time& t);
  virtual unsigned int transport_dbg(tlm::tlm_generic_payload& trans);

  // varibili interne usate per la computazione
  iostruct  ioDataStruct; //struttura
  tlm::tlm_generic_payload* pending_transaction; //transazione in atto
  sc_uint<32> tmp_result0; //risultati temporanei usati per scriverli all'interno della struttura
  sc_uint<32> tmp_result1;

  // funzione definita  
  void xtea_function();

  // costruttore
  SC_HAS_PROCESS(xtea_UT);
  explicit xtea_UT(sc_module_name name_);
  
};

#endif

