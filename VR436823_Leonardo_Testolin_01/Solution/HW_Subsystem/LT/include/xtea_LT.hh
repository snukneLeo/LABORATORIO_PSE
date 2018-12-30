#ifndef __xtea_LT_HPP__
#define __xtea_LT_HPP__

#include <systemc.h>
#include <tlm.h>
#include "define_LT.hh"

class xtea_LT
  : public sc_module
  , public virtual tlm::tlm_fw_transport_if<>
{

 public:
  
  // TLM socket
  tlm::tlm_target_socket<> target_socket;

  //funzioni definite in quanto la classe richiede questi metodi
  virtual void b_transport(tlm::tlm_generic_payload& trans, sc_time& t);
  virtual bool get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmi_data);
  virtual unsigned int transport_dbg(tlm::tlm_generic_payload& trans);
  
  void end_of_elaboration(); 
  void reset(); 
  
  // primitiva nb_blocking
  virtual tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_time& t);

  // varibili interne usate per la computazione
  iostruct  ioDataStruct; //struttura
  tlm::tlm_generic_payload* pending_transaction; //transazione in atto
  sc_uint<32> tmp_result0; //risultati temporanei usati per scriverli all'interno della struttura
  sc_uint<32> tmp_result1;
  //annotazione di tempo per la descrizione LT e temporal decoupling
  sc_time timing_annotation;

  // funzione xtea
  void xtea_function();
  SC_HAS_PROCESS(xtea_LT);
  xtea_LT(sc_module_name name_);
  
};

#endif

