#include "eln_source.h"

// 1 kHz sinusoidal source with an amplitude of 1 mV
eln_source::eln_source(sc_core::sc_module_name _name) :
        out("out"), eln2tdf("eln2tdf"), v_src("v_src", 0.0, 0.0, 1.0e-3, 1.0e3), gnd("gnd") {
    // Set module timestep to 0.25 ms
    v_src.set_timestep(25, sc_core::SC_NS);
    v_src.p(n1);
    v_src.n(gnd);

    eln2tdf.p(n1);
    eln2tdf.n(gnd);
    eln2tdf.outp(out);
}

eln_source::~eln_source() {

}
