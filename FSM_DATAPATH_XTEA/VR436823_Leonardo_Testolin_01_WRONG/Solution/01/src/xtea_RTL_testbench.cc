#include "xtea_RTL_testbench.hh"
#include <cstdlib>
#include <ctime>

xtea_RTL_testbench::xtea_RTL_testbench(sc_module_name name_)
    : sc_module(name_)
{

    SC_THREAD(run);
    sensitive << clk.pos();

    SC_THREAD(clk_gen);
}

void xtea_RTL_testbench::clk_gen()
{
    while( true )
    {
        clk.write( sc_dt::SC_LOGIC_1 );
        wait(PERIOD / 2, sc_core::SC_NS);
        clk.write( sc_dt::SC_LOGIC_0 );
        wait(PERIOD / 2, sc_core::SC_NS);
    }
}

void xtea_RTL_testbench::run()
{
    sc_uint<32> resulttemp1;

    mode.write(0); //encript
    wait(500);
    word0.write(0x12345678); 
    wait(500);
    word1.write(0x9abcdeff); 
    wait(500);
    key0.write(0x6a1d78c8); 
    wait(500);
    key1.write(0x8c86d67f); 
    wait(500);
    key2.write(0x2a65bfbe); 
    wait(500);
    key3.write(0xb4bd6e46); 
    wait(500);
    din_rdy.write(1);
    wait(500);

    while(dout_rdy.read() != 1) wait();
        cout << "result0: " << result0.read() << endl;
    resulttemp1 = result0.read();

    din_rdy.write(0);
    rst.write(1);
    wait(1000);
    mode.write(1); //decryption
    wait(500);
  
    word0.write(result0.read());
    wait(500);
    word1.write(result1.read());

    din_rdy.write(1);
    while(dout_rdy.read() != 1) wait();
    cout << "result1: " << result1.read() << endl;
    wait(500);


    if((result0.read() != 0x99bbb92b) || (result1.read() != 0x3ebd1644))
        printf("Wrong result!"); 

    rst.write(1);
    din_rdy.write(1);
    sc_stop();
}


