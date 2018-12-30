#ifndef TRANSACTOR_RTL_AMS_HPP
#define TRANSACTOR_RTL_AMS_HPP

#include "systemc-ams.h"

SCA_TDF_MODULE(Transactor_RTL_AMS)
{
public:
  //dichiarazione di tutti i segnali per la comunicazione dei moduli
  sca_tdf::sca_out<double> threshold_ams;
  sca_tdf::sca_out<sc_uint<32> > command_ams;

  //ingressi del transattore e le uscite vengono convertire in ams
  sca_tdf::sca_de::sca_in<double> threshold_rtl;
  sca_tdf::sca_de::sca_in<sc_uint<32> > word0_rtl;
  sca_tdf::sca_de::sca_in<sc_uint<32> > word1_rtl;
  sca_tdf::sca_de::sca_in<bool> dout;

  //costruttore
  Transactor_RTL_AMS(sc_core::sc_module_name);

  //metodi
  void set_attribute();
  void processing();
};

#endif
