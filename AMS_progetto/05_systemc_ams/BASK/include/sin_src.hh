#ifndef SIN_SRC_HH
#define SIN_SRC_HH

#include "systemc.h"
#include "systemc-ams.h"

SCA_TDF_MODULE( sin_src )
{

    sca_tdf::sca_out< double > out; //output port

    sin_src( 
            sc_core::sc_module_name nm,
            double ampl_,
            double freq_,
            sca_core::sca_time Tm
           );

    void set_attributes();

    void processing();

    private:
    double ampl;
    double freq;
    sca_core::sca_time Tm;

};

#endif
