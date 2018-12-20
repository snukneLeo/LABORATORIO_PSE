#ifndef __root_LT_HPP__
#define __root_LT_HPP__

#include <systemc.h>
#include <tlm.h>
#include "define_LT.hh"

class root_LT
  : public sc_module
  , public virtual tlm::tlm_fw_transport_if<>
{

 public:

  tlm::tlm_target_socket<> target_socket;

  virtual void b_transport(tlm::tlm_generic_payload& trans, sc_time& t);

  virtual bool get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmi_data);

  virtual tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_time& t);

  virtual unsigned int transport_dbg(tlm::tlm_generic_payload& trans);

  iostruct  ioDataStruct;
  tlm::tlm_generic_payload* pending_transaction;
  sc_int<32> tmp_result;
  sc_time timing_annotation;

  void root_function();


  void end_of_elaboration();

  void reset();
  
  SC_HAS_PROCESS(root_LT);

  root_LT(sc_module_name name_);
  
};

#endif

