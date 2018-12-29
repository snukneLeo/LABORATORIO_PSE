#ifndef VALVE_TDF_HH
#define VALUE_TDF_HH


#include "systemc-ams.h"
#include "systemc.h"
#include "command_enum.hh"

SCA_TDF_MODULE (valve)
{
    public:
        sca_tdf::sca_in<int > command; //due ingressi
        sca_tdf::sca_in<double > thresholding;
        sca_tdf::sca_out<double > current_aperture; //una uscita
        
        valve( sc_core::sc_module_name);
        //~valve();

        //module and ports attributes
        void set_attributes();
        //time-domain signal processing behavior or algortim
        void processing();

    private:
        double current_valve;
};
#endif