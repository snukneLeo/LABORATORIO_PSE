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
    uint32_t word0, word1, key0, key1, key2, key3;  
    bool mode;
    uint32_t result0, result1; 

    mode = 0; //encript
    word0 = 0x12345678; 
    word1 = 0x9abcdeff; 
    key0 = 0x6a1d78c8; 
    key1 = 0x8c86d67f; 
    key2 = 0x2a65bfbe; 
    key3 = 0xb4bd6e46; 

    din_rdy.write(1);
    dout_rdy.read();
    rst.write(0);

    //xtea(din_rdy,word0, word1, key0, key1, key2, key3, mode, &result0, &result1,dout_rdy,clk,rst);
    cout<<"First invocation:" <<endl;
    cout<< "   - the encryption of "<< word0 << " and "<< word1 <<endl; 
    //printf("   - with key %x%x%x%x \n", key0, key1, key2, key3);
    cout <<"with key0: " << key0 << " e key1 " << key1 << " e key2" << key2 << " e key3 " << key3 <<endl; 
    cout <<"is: "<< result0 <<", "<<result1 << endl;
    if((result0 != 0x99bbb92b) || (result1 != 0x3ebd1644))
        cout << "Result wrong!" << endl;
    
    // printf("Second invocation: \n"); 
    mode = 1; //decryption
    
    word0 = result0;
    word1 = result1;

    key0 = 0x6a1d78c8; 
    key1 = 0x8c86d67f; 
    key2 = 0x2a65bfbe; 
    key3 = 0xb4bd6e46; 
    
    //xtea_RTL_main(din_rdy,word0, word1, key0, key1, key2, key3, mode, result0, result1);
    cout << "Second invocation " << endl;
    cout<< "   - the encryption of "<< word0 << " and "<< word1 <<endl; 
    cout <<"with key0: " << key0 << " e key1 " << key1 << " e key2" << key2 << " e key3 " << key3 <<endl; 
    cout <<"is: "<< result0 <<", "<<result1 << endl;

    if((result0 != 0x12345678) || (result1 != 0x9abcdeff))
        cout << "Result wrong!" << endl;
        
    cout << "Done!" <<endl;

    rst.write(1);
    din_rdy.write(0);

    sc_stop();
}


