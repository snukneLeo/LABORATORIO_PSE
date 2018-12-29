#ifndef TESTBENCH_HH
#define TESTBENCH_HH

#include "systemc.h"
#include "systemc-ams.h"
#include "RTL-AMS_transactor.hpp"
#include "TLM-RTL_transactor.hpp"
#include "Controller_TLM.hpp"
#include "AMS-RTL_transactor.hpp"
#include "RTL-TLM_transactor.hpp"
#include "Valve.hpp"
#include "Water_tank.hpp"
#include "Xtea_RTL.hpp"

#define PERIOD 10

class testbench_AMS: public sc_core::sc_module
{
    public:
        testbench_AMS(sc_core::sc_module_name);
        SC_HAS_PROCESS(testbench_AMS);
        //collegamento per rtl
        sc_signal<double > thresh;
        sc_signal<sc_uint<32> > word0_rtl;
        sc_signal<sc_uint<32> > word1_rtl;
        sc_signal<sc_uint<32> > word0_dec_rtl;
        sc_signal<sc_uint<32> > word1_dec_rtl;
        sca_tdf::sca_signal<double > thresh_ams;
        sca_tdf::sca_signal<sc_uint<32> > command_ams;
        sca_tdf::sca_signal<double > aperture;
        sca_tdf::sca_signal<double > water_level_ams;
        sc_signal<double > water_level_rtl;

        sc_signal<sc_uint<32> > key0;
        sc_signal<sc_uint<32> > key1;
        sc_signal<sc_uint<32> > key2;
        sc_signal<sc_uint<32> > key3;
        sc_signal<sc_uint<1> > mode;
        sc_signal<bool> reset;
        sc_signal<bool> din;
        sc_signal<bool> dout;
        sc_signal<sc_logic> clock; 
        sc_out<sc_logic> clock_out;

        TLM_controller controller;
        TLM_TO_RTL tlm_to_rtl;
        XTEA_RTL xtea;
        RTL_TO_TDF rtl_to_tdf;
        Valve valvola;
        waterTank_TDF tank;
        AMS_TO_RTL ams_to_rtl;
        RTL_TO_TLM rtl_to_tlm;
        void clock_gen();  
};

#endif