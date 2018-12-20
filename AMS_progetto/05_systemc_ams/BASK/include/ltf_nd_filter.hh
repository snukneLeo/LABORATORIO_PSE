#ifndef LTF_ND_FILTER_HH
#define LTF_ND_FILTER_HH

#include "systemc-ams.h"

class ltf_nd_filter : public sca_tdf::sca_module
{
    public:
        sca_tdf::sca_in< double > in;
        sca_tdf::sca_out< double > out;

        ltf_nd_filter( sc_core::sc_module_name, double, double );

        void initialize();

        void processing();

    private:
        sca_tdf::sca_ltf_nd ltf_nd; //Laplace transfer function
        sca_util::sca_vector< double > num, den; //numerator and denominator coeff
        double fc; // 3dB cut-off frequency in Hz
        double h0; //DC gain
};

#endif
