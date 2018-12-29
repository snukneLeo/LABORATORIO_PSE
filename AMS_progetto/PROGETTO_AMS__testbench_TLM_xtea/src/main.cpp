#include"struct.hh"
#include<systemc.h>
#include<systemc-ams.h>
#include"AMS-testbench.hpp"

int sc_main( int ac, char *av[] )
{
    testbench_AMS test("testbench");

    sca_trace_file *file = sca_create_vcd_trace_file("water");
    sca_trace(file, test.water_level_ams, "water_level");
    sca_trace(file,test.command_ams,"comand");
    sca_trace(file,test.aperture,"aperture");
    sca_trace(file,test.thresh_ams,"threshold");
    sc_trace_file *fileSC=sc_create_vcd_trace_file("wave");
    fileSC->set_time_unit(1,SC_NS);
    sc_trace(fileSC,test.clock,"clock");
    sc_trace(fileSC,test.reset,"reset");
    sc_trace(fileSC,test.mode,"mode");
    sc_trace(fileSC,test.word0_rtl,"word0");
    sc_trace(fileSC,test.xtea.word0,"wor0_processed");
    sc_trace(fileSC,test.word0_dec_rtl,"word0_decr");
    sc_trace(fileSC,test.word1_rtl,"wor1");
    sc_trace(fileSC,test.xtea.word1,"wor1_processed");
    sc_trace(fileSC,test.word1_dec_rtl,"word1_decr");
    sc_trace(fileSC,test.din,"d-in");
    sc_trace(fileSC,test.xtea.STATUS,"Stato");
    sc_start(1200,SC_SEC);
    sca_close_vcd_trace_file(file);

}