#ifndef CONTROLLER_IFACE_HH
#define CONTROLLER_IFACE_HH

#include "systemc-ams.h"

SCA_TDF_MODULE( controller_iface )
{
  public:
    sca_tdf::sca_in< double > inc;
    sca_tdf::sca_out< double > outc;

    sca_tdf::sca_de::sca_in< double > inp;
    sca_tdf::sca_de::sca_out< double > outp;

    controller_iface( sc_core::sc_module_name );

    ~controller_iface();

    void set_attribute();
    void processing();

};

#endif //CONTROLLER_IFACE_HH
