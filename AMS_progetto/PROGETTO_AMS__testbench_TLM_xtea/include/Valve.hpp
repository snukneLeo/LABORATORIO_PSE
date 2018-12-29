#ifndef VALVE_HH
#define VALVE_HH

#include<systemc.h>
#include<systemc-ams.h>
#include"command_enum.hh"

SCA_TDF_MODULE(Valve)
{
    private:
        double current_valve;
    public:
        sca_tdf::sca_in<sc_uint<32> > command;
        sca_tdf::sca_in<double> thresholding;
        sca_tdf::sca_out<double> current_aperture;
        Valve(sc_core::sc_module_name name);
        void set_attribute();
        void processing();
};

#endif 