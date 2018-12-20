#include "ltf_nd_filter.h"

ltf_nd_filter::ltf_nd_filter(sc_core::sc_module_name nm, double fc_, double h0_) :
        in("in"), out("out"), fc(fc_), h0(h0_) {
}
void ltf_nd_filter::initialize() {
    num(0) = 1.0;
    den(0) = 1.0;
    den(1) = 1.0 / (2.0 * M_PI * fc);
}
void ltf_nd_filter::processing() {
    out.write(ltf_nd(num, den, in.read(), h0));
}
