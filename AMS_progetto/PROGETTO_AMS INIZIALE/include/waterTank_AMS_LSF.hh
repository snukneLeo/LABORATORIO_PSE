#ifndef WATER_LSF_HH
#define WATER_LSF_HH

#include "systemc-ams.h"

class waterTank : public sc_core::sc_module
{
    public:

        sca_tdf::sca_in<double > in; //ingresso dalla valvola
        sca_tdf::sca_out<double > out; //uscita dal watertank (ingresso del controller)

        waterTank(sc_core::sc_module_name );
        //~waterTank();
    
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
        sca_lsf::sca_signal sig1,sig2,sig3,sig4,sig5;//,sig6,sig7;    
};

#endif