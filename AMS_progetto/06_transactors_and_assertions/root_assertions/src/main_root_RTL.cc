#include <systemc.h>
#include "root_RTL_testbench.hh"
#include "root_RTL.hh"

SC_MODULE(main_RTL)
{
  
  // CLOCK SIGNAL
  sc_signal< sc_logic >     clk;

  // RESET SIGNAL
  sc_signal < bool >        rst;
  
  // OTHER SIGNALS
  sc_signal<sc_uint<1> >  	dout_rdy;
  sc_signal<sc_uint<32> > 	dout;
  sc_signal<sc_uint<1> >  	din_rdy;
  sc_signal<sc_uint<32> > 	din;
 
 


  //Definition   
  root_RTL_testbench		tb;	       // source module
  root_RTL			root;    // root RTL module
    
  //Construct
  SC_CTOR(main_RTL)
    : tb("tb")
    , root("root")
  {
      
    root.clk(clk);
    root.rst(rst);
    root.din(din);
    root.din_rdy(din_rdy);
    root.dout(dout);
    root.dout_rdy(dout_rdy);
 
    tb.clk(clk);
    tb.rst(rst);
    tb.din(din);
    tb.din_rdy(din_rdy);
    tb.dout(dout);
    tb.dout_rdy(dout_rdy);
 
	
  }

};

int sc_main(int argc, char **argv)
{
  sc_report_handler::set_actions("/IEEE_Std_1666/deprecated", SC_DO_NOTHING);
  main_RTL* topl;

  topl = new main_RTL("topl");

  sc_start();

  return(0);

};


