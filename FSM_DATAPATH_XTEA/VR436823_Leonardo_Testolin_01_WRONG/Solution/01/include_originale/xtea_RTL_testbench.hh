#ifndef xtea_RTL_TESTBENCH_H
#define xtea_RTL_TESTBENCH_H

#define PERIOD 10

#include <systemc.h>

class xtea_RTL_testbench : public sc_core::sc_module
{

    private:
        //metodi
        void run();
        void clk_gen();

    public:

        sc_out<bool>           rst;
        sc_out< sc_dt::sc_logic > clk;

        sc_out<sc_uint<1> >    din_rdy;
        sc_out<sc_uint<32> >   word0;
        sc_out<bool>           mode;
        sc_out<sc_uint<32> >   word1;
        sc_out<sc_uint<32> >   key0;
        sc_out<sc_uint<32> >   key1;
        sc_out<sc_uint<32> >   key2;
        sc_out<sc_uint<32> >   key3;
       


        sc_in<sc_uint<32> >  result0;
        sc_in<sc_uint<32> >  result1;
        sc_in<sc_uint<1> >   dout_rdy;

        SC_HAS_PROCESS(xtea_RTL_testbench);
        xtea_RTL_testbench(sc_module_name name);

};

#endif
