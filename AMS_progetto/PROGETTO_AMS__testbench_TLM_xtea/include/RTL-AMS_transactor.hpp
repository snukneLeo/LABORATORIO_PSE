#ifndef TRANSATTORE_FROM_RTL_TO_TDF_HH
#define TRANSATTORE_FROM_RTL_TO_TDF_HH
#include "systemc-ams.h"

SCA_TDF_MODULE(RTL_TO_TDF)
{
  public:
    sca_tdf::sca_out<double> threshold_AMS;
    sca_tdf::sca_out<sc_uint<32> > command_AMS;
    sca_tdf::sca_de::sca_in<double> threshold_rtl;
    sca_tdf::sca_de::sca_in<sc_uint<32> > word0_rtl;
    sca_tdf::sca_de::sca_in<sc_uint<32> > word1_rtl;

    RTL_TO_TDF(sc_core::sc_module_name);

    void set_attribute();
    void processing();
};

#endif