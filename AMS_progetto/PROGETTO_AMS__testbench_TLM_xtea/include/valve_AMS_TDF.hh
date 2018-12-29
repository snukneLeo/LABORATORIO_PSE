#ifndef VALVE_TDF_HH
#define VALUE_TDF_HH
#include "command_enum.hh"

SCA_TDF_MODULE (AMS_valve_TDF)
{
    public:
        sca_tdf::sca_in<sc_uint<32> > command; //due ingressi
        sca_tdf::sca_in<double > thresholding;
        sca_tdf::sca_out<double > current_aperture; //una uscita
        
        AMS_valve_TDF( sc_core::sc_module_name);

        //module and ports attributes
        void set_attributes();
        //time-domain signal processing behavior or algortim
        void processing();

    private:
        double current_valve;
};
#endif