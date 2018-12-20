#ifndef SYSTEM_HH
#define SYSTEM_HH

#include "controller_tdf.hh"
#include "ControllerIFace.hh"
#include "plant_lsf.hh"

#include "ControllerTransactor.hh"
#include "PlantTransactor.hh"


class System : public sc_core::sc_module
{
  public:
    System( sc_core::sc_module_name );
    ~System();

  protected:
    plant p;
    PlantTransactor pt;
    controller c;
    ControllerTransactor ct;
    controller_iface ci;

    sca_tdf::sca_signal< double > sig_tdf_fw, sig_tdf_bw;
    sc_core::sc_signal< double > sig_de_fw, sig_de_bw;

    sc_core::sc_signal< double > sig_pt_fw, sig_pt_bw, sig_ct_fw, sig_ct_bw;

};

#endif //SYSTEM_HH
