#ifndef TESTBENCH_HH
#define TESTBENCH_HH

#include "systemc-ams.h"
#include "systemc.h"
#include "command_enum.hh"

SCA_TDF_MODULE (amsTest)
{
    public:
        sca_tdf::sca_in<double > waterTank; //ingresso da water tank
        sca_tdf::sca_out<double > thresholding;
        sca_tdf::sca_out<int > command;

        amsTest( sc_core::sc_module_name );

        //module and ports attributes
        void set_attributes();
        //time-domain signal processing behavior or algortim
        void processing();
    private:
        int samples;
        int samplesTowait;
        double thresh;
        long int counter;
};
#endif