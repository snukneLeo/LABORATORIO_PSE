#ifndef TESTBENCH_HH
#define TESTBENCH_HH

#include "systemc-ams.h"
#include "systemc.h"
#include "command_enum.hh"

SCA_TDF_MODULE (amsTest)
{
    public:
        //dichiarazione delle porte di ingresso e uscita
        sca_tdf::sca_in<double > waterTank;
        sca_tdf::sca_out<double > thresholding;
        sca_tdf::sca_out<int > command;

        //costruttore
        amsTest( sc_core::sc_module_name );

        //module and ports attributes
        void set_attributes();
        //time-domain signal processing behavior or algortim
        void processing();
        //varibili private usate per il funzionanamneto
    private:
        int samples; //sample da inviare
        int samplesTowait; //sample da accumulare
        double thresh;
        long int counter; //contatore per il conto dei campioni
};
#endif