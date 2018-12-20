#include "lsf_in_tdf.h"

lsf_in_tdf::lsf_in_tdf(sc_core::sc_module_name) :
        in("in"), out("out"), add1("add1"), dot1("dot1"), gain1("gain1"), tdf2lsf("tdf2lsf"), lsf2tdf("lsf2tdf"), sig1("sig1"), sig2("sig2"), sig3("sig3"), sig4("sig4") {

    /* TDF Input Ports. */
    tdf2lsf.inp(in);
    tdf2lsf.y(sig1);

    /* Internal LSF Equation System. */
    add1.x1(sig1);
    add1.x2(sig3);
    add1.y(sig2);

    dot1.x(sig2);
    dot1.y(sig4);

    gain1.x(sig4);
    gain1.y(sig3);

    /* TDF Output Ports. */
    lsf2tdf.x(sig4);
    lsf2tdf.outp(out);
}

lsf_in_tdf::~lsf_in_tdf() {

}
