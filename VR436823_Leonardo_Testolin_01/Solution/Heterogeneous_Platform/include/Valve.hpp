#ifndef VALVE_HPP
#define VALVE_HPP

#include<systemc.h>
#include<systemc-ams.h>
#include"Commands.hpp"

SCA_TDF_MODULE(Valve)
{
    public:
        //dichiarazione delle porte di ingresso e uscita
        sca_tdf::sca_in<sc_uint<32> > command;
        sca_tdf::sca_in<double > thresholding;
        sca_tdf::sca_out<double > current_aperture;
        //costruttore
        Valve( sc_core::sc_module_name);

        //module and ports attributes
        void set_attributes();
        //time-domain signal processing behavior or algortim
        void processing();
    //varibili private usate per il funzionanamneto
    private:
        double current_valve; //varibile interna per tenere traccia della apertura
};

#endif 