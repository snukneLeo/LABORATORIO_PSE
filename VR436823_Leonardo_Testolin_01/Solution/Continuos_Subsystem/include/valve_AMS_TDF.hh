#ifndef VALVE_TDF_HH
#define VALUE_TDF_HH


#include "systemc-ams.h"
#include "systemc.h"
#include "command_enum.hh"

SCA_TDF_MODULE (valve)
{
    public:
        //dichiarazione delle porte di ingresso e uscita
        sca_tdf::sca_in<int > command;
        sca_tdf::sca_in<double > thresholding;
        sca_tdf::sca_out<double > current_aperture;
        //costruttore
        valve( sc_core::sc_module_name);

        //module and ports attributes
        void set_attributes();
        //time-domain signal processing behavior or algortim
        void processing();
    //varibili private usate per il funzionanamneto
    private:
        double current_valve; //varibile interna per tenere traccia della apertura
};
#endif