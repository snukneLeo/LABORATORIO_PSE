#include "mixer_de.h"

mixer_de::mixer_de(sc_core::sc_module_name nm) :
        in_bin("in_bin"), in_wav("in_wav"), out("out"), rate(40) {
}

void mixer_de::set_attributes() {
    in_wav.set_rate(rate);
    out.set_rate(rate);
}

void mixer_de::processing() {
    for (unsigned long i = 0; i < rate; i++) {
        if (in_bin.read()) {
            out.write(in_wav.read(i), i);
        }
        else out.write(0.0, i);
    }
}
