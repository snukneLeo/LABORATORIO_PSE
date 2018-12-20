#ifndef LSF_CONVERTER_H
#define LSF_CONVERTER_H

#include <systemc-ams>

SC_MODULE(lsf_in_tdf) {
    public:
        //--------------------Ports for TDF-----------------------------
        /* TDF Input Ports. */
        sca_lsf::sca_tdf::sca_source tdf2lsf;
        sca_tdf::sca_in<double> in;

        /* TDF Output Ports. */
        sca_lsf::sca_tdf::sca_sink lsf2tdf;
        sca_tdf::sca_out<double> out;

        //--------------------Local Declaration Here--------------------
        sca_lsf::sca_add add1;
        sca_lsf::sca_dot dot1;
        sca_lsf::sca_gain gain1;

        lsf_in_tdf(sc_core::sc_module_name);

        ~lsf_in_tdf();

    private:
        sca_lsf::sca_signal sig1, sig2, sig3, sig4;
};

#endif
