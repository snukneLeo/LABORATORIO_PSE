#include <systemc.h>
#include <tlm.h>
#include "root_LT_testbench.hh"
#include "root_RTL_transactor.hh"
#include "root_RTL.hh"

#define PERIOD 10

SC_MODULE(main_RTL)
{
  
  // CLOCK SIGNAL
  sc_signal< sc_dt::sc_logic > clk;

  void clk_gen()
  {
    while( true )
    {
      clk.write( sc_dt::SC_LOGIC_1 );
      wait( PERIOD / 2, sc_core::SC_NS );
      clk.write( sc_dt::SC_LOGIC_0 );
      wait( PERIOD / 2, sc_core::SC_NS );   
    }
  }

  // RESET SIGNAL
  sc_signal < bool >        rst;
  
  // OTHER SIGNALS
  sc_signal<sc_uint<1> >  	dout_rdy;
  sc_signal<sc_uint<32> > 	dout;
  sc_signal<sc_uint<1> >  	din_rdy;
  sc_signal<sc_uint<32> > 	din;

  //Definition   
  root_LT_testbench		  tb;	       // source module
  root_RTL_transactor		transactor; // root transactor  
  root_RTL			        root;    // root RTL module
    
  //Construct
  SC_CTOR(main_RTL)
    : tb("tb")
    , transactor("transactor")
    , root("root")
  {
      
    SC_THREAD( clk_gen );

    // TLM testbench <-> Transactor binding (TLM interface)
    tb.initiator_socket(transactor.target_socket);
		
    // RTL design <-> Transactor binding (RTL interfaces)
    root.clk(clk);
    root.rst(rst);
    root.din_rdy(din_rdy);
    root.din(din);
    root.dout(dout);
    root.dout_rdy(dout_rdy);
 

    transactor.clk(clk);
    transactor.rst(rst);
    transactor.din_rdy(din_rdy);
    transactor.din(din);
    transactor.dout(dout);
    transactor.dout_rdy(dout_rdy);
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


