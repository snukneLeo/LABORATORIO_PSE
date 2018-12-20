#ifndef PLANT_LSF_HH
#define PLANT_LSF_HH

#include <systemc-ams.h>

class plant : public sc_core::sc_module
{

  public:
    
    sc_core::sc_in< double > in;
    sc_core::sc_out< double > out;

    plant( sc_core::sc_module_name );
    ~plant();

  protected:

    sca_lsf::sca_de::sca_source x;
    sca_lsf::sca_de::sca_sink y;

    sca_lsf::sca_signal sig;


};

#endif //PLANT_LSF_HH
