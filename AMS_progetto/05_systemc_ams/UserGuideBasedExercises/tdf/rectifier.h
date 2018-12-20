#ifndef RECTIFIER_H
#define RECTIFIER_H

#include <systemc-ams>

SCA_TDF_MODULE(rectifier) {
    public:
        sca_tdf::sca_in<double> in;
        sca_tdf::sca_out<double> out;

        rectifier(sc_core::sc_module_name _name);

        void processing();
};

#endif
