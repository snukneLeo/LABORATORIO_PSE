#include <systemc-ams>
#include <systemc>

//----------LSF Modules----------
#include "lsf/lsf_in_tdf.h"

//----------ELN Modules----------
#include "eln/eln_source.h"

//----------TDF Modules----------
#include "tdf/ltf_nd_filter.h"
#include "tdf/rectifier.h"
#include "tdf/mixer_de.h"
#include "tdf/bit_src.h"
#include "tdf/sin_src.h"
#include "tdf/sampler.h"
#include "tdf/mixer.h"

int sc_main(int argc, char* argv[]) {
    sc_core::sc_set_time_resolution(1.0, sc_core::SC_FS);

    //--------------------Local Ports Here--------------------
    sca_tdf::sca_signal<bool> in_bits;
    sca_tdf::sca_signal<double> in_wave;
    sca_tdf::sca_signal<double> wave;
    sca_tdf::sca_signal<double> out_wave;

    sca_tdf::sca_signal<bool> out_bits;

    //---------------------Modules Here-----------------------
    bit_src bit_generator("bit_generator");
    eln_source source("source");
    mixer mix("mix");
    lsf_in_tdf lsf_module("lsf_module");
//    sampler smp("smp");

    //-----------------Interconnections Here------------------
    //-----ELN Modules-----
    source.out(in_wave);

    //-----TDF Modules-----
    bit_generator.out(in_bits);

    mix.in_wav(in_wave);
    mix.in_bin(in_bits);
    mix.out(wave);

    //-----LSF Modules-----
    lsf_module.in(wave);
    lsf_module.out(out_wave);

    //-----------------------Traces Here----------------------
    sca_util::sca_trace_file * atf = sca_util::sca_create_vcd_trace_file("trace.vcd");
    sca_util::sca_trace(atf, in_bits   , "in_bits");
    sca_util::sca_trace(atf, in_wave   , "wave_1");
    sca_util::sca_trace(atf, wave      , "wave_2");
    sca_util::sca_trace(atf, out_wave  , "wave_3");

    //-----------------------Start Here-----------------------
    sc_core::sc_start(1, sc_core::SC_MS);

    //--------------------Close Traces Here-------------------
    sca_util::sca_close_vcd_trace_file(atf);

    return 0;
}
