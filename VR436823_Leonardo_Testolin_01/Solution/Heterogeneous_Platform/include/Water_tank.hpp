#ifndef WATER_TANK_HPP
#define WATER_TANK_HPP

#include <systemc.h>
#include <systemc-ams.h>
//LSF
class Water_tank:public sc_core::sc_module
{
    public:
        sca_tdf::sca_in<double > in; //ingresso dalla valvola
        sca_tdf::sca_out<double > out; //uscita dal watertank (ingresso del controller)
        //costruttore
        Water_tank(sc_core::sc_module_name );
    
        //conversione tra ingresso tdf e lsf
        sca_lsf::sca_tdf::sca_source convertion;
        //convertion tdf to lsf
        sca_lsf::sca_tdf::sca_sink convertionLSFtoTDF;
        //moltiplicatore
        sca_lsf::sca_gain gainA;
        //sottrazione
        sca_lsf::sca_sub subTwoSignal;
        //integratore
        sca_lsf::sca_integ integratore;
        //moltiplicatore
        sca_lsf::sca_gain gainK2;
        //segnali uscenti ed entranti dei diversi moduli creati
        sca_lsf::sca_signal sig1,sig2,sig3,sig4,sig5;    
};

#endif