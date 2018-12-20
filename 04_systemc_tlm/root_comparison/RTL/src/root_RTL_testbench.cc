#include "root_RTL_testbench.hh"

  root_RTL_testbench::root_RTL_testbench(sc_module_name name_)
: sc_module(name_)
{

  SC_THREAD(run);
  sensitive << clk.pos();

  SC_THREAD(clk_gen);
}

void root_RTL_testbench::clk_gen()
{
  while( true )
  {
    clk.write( sc_dt::SC_LOGIC_1 );
    wait(PERIOD / 2, sc_core::SC_NS);
    clk.write( sc_dt::SC_LOGIC_0 );
    wait(PERIOD / 2, sc_core::SC_NS);
  }
}

void root_RTL_testbench::run()
{

  sc_uint<32> temp_data_in, result = 0;

//  cout<<"Calculate the square root of 10000000  numbers!"<<endl;

  for (int i = 1; i <= 10000000; i++){
    wait();
    reset_to_RTL.write(0);
    wait();
    reset_to_RTL.write(1);
    wait();
    temp_data_in = (rand() % 256);

//    cout<<"\tThe square root of "<<temp_data_in;

    reset_to_RTL.write(1);
    p_Out_data.write(temp_data_in);

    p_Out_enable.write(1);
    wait();

    while(p_In_enable.read() != 1) wait();
    result=p_In_data.read();
//    cout << "\t is: " << result << endl;

  }

  reset_to_RTL.write(0);
  p_Out_enable.write(0);
  p_Out_data.write(0);

  sc_stop();

}


