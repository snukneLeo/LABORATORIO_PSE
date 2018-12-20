#include "rectifier.h"

rectifier::rectifier(sc_core::sc_module_name _name) :
        in("in"), out("out") {
}

void rectifier::processing() {
    out.write(std::abs(in.read()));
}
