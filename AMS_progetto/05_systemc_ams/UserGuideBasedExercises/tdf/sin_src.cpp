#include "sin_src.h"

sin_src::sin_src(sc_core::sc_module_name nm, double ampl_, double freq_, sca_core::sca_time Tm_) :
        out("out"), ampl(ampl_), freq(freq_), Tm(Tm_) {

}
void sin_src::set_attributes() {
    set_timestep(Tm);
}
void sin_src::processing() {
    double t = get_time().to_seconds(); // actual time
    out.write(ampl * std::sin(2.0 * M_PI * freq * t));
}
