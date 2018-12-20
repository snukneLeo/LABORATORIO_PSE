#include "bit_src.h"

bit_src::bit_src(sc_core::sc_module_name nm) :
        out("out") {

}

void bit_src::processing() {
    out.write((bool) (std::rand() % 2));
}
