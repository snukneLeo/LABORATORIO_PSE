#include "mixer.h"

mixer::mixer(sc_core::sc_module_name nm) :
        in_bin("in_bin"), in_wav("in_wav"), out("out"), rate(40) {
    // use a carrier data rate of 40
}

void mixer::set_attributes() {
    in_wav.set_rate(rate);
    out.set_rate(rate);
}
void mixer::processing() {
    for (unsigned long i = 0; i < rate; i++) {
        if (in_bin.read()) {
            out.write(in_wav.read(i), i);
        }
        else out.write(0.0, i);
    }
}
