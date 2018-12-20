#include "sampler.h"

sampler::sampler(sc_core::sc_module_name _name) :
        in("in"), out("out"), rate(20000), threshold(0.5) {
}

void sampler::set_attributes() {
    in.set_rate(rate);                    // Port samples/timestep.
    in.set_timestep(25, sc_core::SC_NS);
    out.set_delay(1);                     // Port out is delayed by one timestep.
}

void sampler::processing() {
    double val = 0.0;
    for (int i = 0; i < in.get_rate(); i++) {
        val += abs(in.read(i));
    }
    if (val > threshold) {
        out.write(false);
    }
    else out.write(true);
}
