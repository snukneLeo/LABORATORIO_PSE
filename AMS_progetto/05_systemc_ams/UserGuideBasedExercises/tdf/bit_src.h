#ifndef BIT_SRC_H
#define BIT_SRC_H

#include <systemc-ams.h>

SCA_TDF_MODULE(bit_src) {
        sca_tdf::sca_out<bool> out; // output port

        bit_src(sc_core::sc_module_name nm);

        void processing();

};

#endif
