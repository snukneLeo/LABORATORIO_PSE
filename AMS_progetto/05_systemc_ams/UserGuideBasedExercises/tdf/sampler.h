#ifndef SAMPLER_H
#define SAMPLER_H

#include <systemc-ams>

SCA_TDF_MODULE(sampler) {
    public:
        // Input port.
        sca_tdf::sca_in<double> in;
        // Output port.
        sca_tdf::sca_out<bool> out;

        sampler(sc_core::sc_module_name _name);

        void set_attributes();

        void processing();

    private:
        unsigned long rate;
        double threshold;
};

#endif
