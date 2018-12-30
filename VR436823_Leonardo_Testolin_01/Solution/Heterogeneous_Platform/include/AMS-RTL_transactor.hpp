#ifndef TRANSACTOR_AMS_RTL_HPP
#define TRANSACTOR_AMS_RTL_HPP

#include "systemc-ams.h"

SCA_TDF_MODULE( Transactor_AMS_RTL ) //transattore
{
  public:
    //definizione dei segnali di ingresso e uscita
    sca_tdf::sca_in< double > water_level_ams; //ingresso ams
    sca_tdf::sca_de::sca_out< double > water_level_rtl; //uscita rtl
    Transactor_AMS_RTL( sc_core::sc_module_name );

    //metodi
    void set_attribute();
    void processing();

};

#endif 
