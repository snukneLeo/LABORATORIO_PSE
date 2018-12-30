#include <systemc-ams.h>
#include "systemc.h"
#include "AMS_TDF_testbench.hh"
#include "valve_AMS_TDF.hh"
#include "waterTank_AMS_LSF.hh"



int sc_main(int argc, char **argv)
{
    //dichiarazione dei segnali di ingresso e uscita
    sca_tdf::sca_signal<double > waterLevel; //ingresso da water tank
    sca_tdf::sca_signal<double > thresholding;
    sca_tdf::sca_signal<int > command;
    sca_tdf::sca_signal<double > current_aperture;


    valve valve("valve");
    waterTank waterTank("waterTank");
    amsTest test("test");

    //collegamento dei diversi moduli con i segnali
    valve.command(command);
    valve.thresholding(thresholding);
    valve.current_aperture(current_aperture);

    waterTank.in(current_aperture);
    waterTank.out(waterLevel);

    test.waterTank(waterLevel);
    test.command(command);
    test.thresholding(thresholding);

    sca_trace_file *file = sca_create_vcd_trace_file("water");
    sca_trace(file,waterLevel,"waterLevel");
    sca_trace(file,thresholding,"thresholding");
    sca_trace(file,current_aperture,"current_aperture");
    sca_trace(file,command,"command");

    sc_start(1800,SC_SEC);
    sca_close_vcd_trace_file(file);

}