#ifndef LTF_ND_FILTER_H
#define LTF_ND_FILTER_H

#include <systemc-ams>

SCA_TDF_MODULE(ltf_nd_filter) {
    public:
        sca_tdf::sca_in<double> in;
        sca_tdf::sca_out<double> out;

        ltf_nd_filter(sc_core::sc_module_name nm, double fc_, double h0_ = 1.0);

        void initialize();

        void processing();

    private:
        /* Laplace Transfer Function
         *  The class sca_ltf_nd implements a scaled continuous-time
         *  linear transfer function of the Laplace-domain variable s
         *  in the numerator-denominator form.
         */
        sca_tdf::sca_ltf_nd ltf_nd;
        sca_util::sca_vector<double> num, den;

        // 3dB cut-off frequency in Hz
        double fc;

        // DC gain
        double h0;
};

#endif
