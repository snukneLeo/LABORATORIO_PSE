#ifndef __dist_LT_HPP__
#define __dist_LT_HPP__

#include <systemc.h>
#include <tlm.h>
#include "define_LT.hh"

class dist_LT
  : public sc_module
  , public virtual tlm::tlm_fw_transport_if<>
{

 public:

  tlm::tlm_target_socket<> target_socket;

  virtual void b_transport(tlm::tlm_generic_payload& trans, sc_time& t);
  virtual bool get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmi_data);
  virtual tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_time& t);
  virtual unsigned int transport_dbg(tlm::tlm_generic_payload& trans);

  // data declaration
  iostruct  ioDataStruct;
  tlm::tlm_generic_payload* pending_transaction;
  sc_uint<32> tmp_result;
  sc_uint<32> sum;
  short int cont_is;
  short int address;
  unsigned int image_segment[512];
  sc_time timing_annotation;

  // internal processes and functions
  void dist_function();
  void end_of_elaboration();
  void reset();
  SC_HAS_PROCESS(dist_LT);

  // constructor 
  dist_LT(sc_module_name name_);
  
};

#endif

