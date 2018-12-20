#ifndef MIXER_H
#define MIXER_H

#include <systemc-ams>

SCA_TDF_MODULE(mixer) {
    public:
        // input port baseband signal
        sca_tdf::sca_in<bool> in_bin;

        // input port carrier signal
        sca_tdf::sca_in<double> in_wav;

        // output port modulated signal
        sca_tdf::sca_out<double> out;

        mixer(sc_core::sc_module_name nm);

        void set_attributes();

        void processing();

    private:
        unsigned long rate;
};

#endif
