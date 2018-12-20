#ifndef MIXER_DE_H
#define MIXER_DE_H

#include <systemc-ams>

SCA_TDF_MODULE(mixer_de) {
    public:
        //----------Ports for Discrete-Event Domain-----
        sca_tdf::sca_de::sca_in<bool> in_bin;
        sca_tdf::sca_in<double>       in_wav;
        sca_tdf::sca_out<double>      out;

        mixer_de(sc_core::sc_module_name nm);

        void set_attributes();

        void processing();

    private:
        unsigned long rate;
};

#endif
