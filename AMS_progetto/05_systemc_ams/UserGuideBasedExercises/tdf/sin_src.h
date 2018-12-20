#ifndef SIN_SRC_H
#define SIN_SRC_H

#include <systemc-ams>

SCA_TDF_MODULE(sin_src) {
        // output port
        sca_tdf::sca_out<double> out;

        sin_src(sc_core::sc_module_name nm, double ampl_ = 1.0, double freq_ = 1.0e3, sca_core::sca_time Tm_ = sca_core::sca_time(0.125, sc_core::SC_MS));

        void set_attributes();

        void processing();

    private:
        // amplitude
        double ampl;

        // frequency
        double freq;

        // module time step
        sca_core::sca_time Tm;
};

#endif
