#ifndef root_RTL_TESTBENCH_H
#define root_RTL_TESTBENCH_H

#define PERIOD 10

#include <systemc.h>

class root_RTL_testbench : public sc_core::sc_module
{

private:

  void run();
  void clk_gen();

public:
  
  sc_in<sc_uint<1> >  	dout_rdy;
  sc_in<sc_uint<32> > 	dout;
  sc_out<sc_uint<1> >  	din_rdy;
  sc_out<sc_uint<32> > 	din;
  sc_out< bool > 		    rst;
  sc_out< sc_logic >    clk;

  SC_HAS_PROCESS(root_RTL_testbench);
  root_RTL_testbench(sc_module_name name);

};

#endif
