#include "root_RTL_testbench.hh"
#define V1

    root_RTL_testbench::root_RTL_testbench(sc_module_name name_)
: sc_module(name_)
{

    SC_THREAD(run);
    sensitive << clk.pos();

    SC_THREAD(clk_gen);
}

void root_RTL_testbench::clk_gen()
{
    while(true)
    {
        clk.write(sc_dt::SC_LOGIC_1);
        wait(1, sc_core::SC_US);
        clk.write(sc_dt::SC_LOGIC_0);
        wait(1, sc_core::SC_US);
    }
}

void root_RTL_testbench::run()
{

    //V1
#ifdef V1 
    sc_uint<32> temp_data_in, result = 0;

    cout<<"Calculate the square root of 128  numbers!"<<endl;

    temp_data_in = (rand() % 256);

    cout<<"\tThe square root of "<<temp_data_in<<endl;

    // write data to the module
    rst.write(1);
    din.write(temp_data_in);
    din_rdy.write(1);
    wait();

    // read - wait until data is ready
    while(dout_rdy.read() != 1) wait();
    result=dout.read();
    cout << "\t is: " << result << endl;

    // reset
    rst.write(0);
    din_rdy.write(0);
    din.write(0);

#else
    sc_uint<32> temp_data_in, result = 0;

    cout<<"Calculate the square root of 128  numbers!"<<endl;

    temp_data_in = (rand() % 256);

    cout<<"\tThe square root of "<<temp_data_in<<endl;

    // write data to the module
    rst.write(1);
    din.write(temp_data_in);
    wait();

    result=dout.read();
    cout << "\t is: " << result << endl;

    // reset
    rst.write(0);
    din_rdy.write(0);
    din.write(0);

#endif

    for( int i = 0; i < 5; ++i )
    {
        wait();
    }
    sc_stop();
}


