#include "xtea_RTL_testbench.hh"
#include "xtea_RTL.hh"


// modulo dove definisco i segnali che vanno a collegarsi con i componenti
int sc_main(int argc, char * argv[])
{
    sc_signal< sc_logic >     clk; //segnale di clock
    sc_signal < bool >        rst; //segnale di reset


    //input
    sc_signal <bool> mode;
    sc_signal<sc_uint<32> >   word0;
    sc_signal<sc_uint<32> >   word1;
    sc_signal<sc_uint<32> >   key0;
    sc_signal<sc_uint<32> >   key1;
    sc_signal<sc_uint<32> >   key2;
    sc_signal<sc_uint<32> >   key3;
    sc_signal<sc_uint<1> >    din_rdy;

    //output
    sc_signal<sc_uint<1> >    dout_rdy; //segnale di output ready
    sc_signal<sc_uint<32> >   result0;
    sc_signal<sc_uint<32> >   result1;

    xtea_RTL_testbench        test("test");             // xtea testbench
    xtea_RTL                  xtea("xtea");         // xtea fsm e datapth

    //Segnali di reset e clock
    xtea.clk(clk);
    xtea.rst(rst);

    //input
    xtea.mode(mode);
    xtea.word0(word0);
    xtea.word1(word1);
    xtea.key0(key0);
    xtea.key1(key1);
    xtea.key2(key2);
    xtea.key3(key3);
    xtea.din_rdy(din_rdy);
    
    //output
    xtea.dout_rdy(dout_rdy);
    xtea.result0(result0);
    xtea.result1(result1);

    //Segnali di reset e clock
    test.clk(clk);
    test.rst(rst);


    //input
    test.mode(mode);
    test.word0(word0);
    test.word1(word1);
    test.key0(key0);
    test.key1(key1);
    test.key2(key2);
    test.key3(key3);
    test.din_rdy(din_rdy);

    //output
    test.dout_rdy(dout_rdy);
    test.result0(result0);
    test.result1(result1);

    sc_start();

    return 0;
};

