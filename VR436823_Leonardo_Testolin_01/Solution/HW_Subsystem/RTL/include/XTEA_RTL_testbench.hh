#ifndef XTEA_XTEA_RTL_TESTBENCH_H
#define XTEA_XTEA_RTL_TESTBENCH_H

#include <systemc.h>

SC_MODULE(XTEA_RTL_testbench) 
{
  private:
    //metodo privato per la thread
    void run();

  public:
    sc_in_clk clk;    // segnali di clock
    sc_out<bool> rst; // segnale di reset

    //i segnali che nello xtea_rtl sono input qui sono output e viceversa
    //principio del testbench
    sc_out<sc_uint<32> > word0; 
    sc_out<sc_uint<32> > word1;
    sc_out<sc_uint<32> > key_i0;
    sc_out<sc_uint<32> > key_i1;
    sc_out<sc_uint<32> > key_i2;
    sc_out<sc_uint<32> > key_i3;

    //ingressi
    sc_in<sc_uint<32> > out0;
    sc_in<sc_uint<32> > out1;
    //output pronto
    sc_in<bool> dout_rdy;

    sc_out<bool> input_ready; // input pronto
    sc_out<sc_uint<1> > mode; //modalità da scegliere

    SC_HAS_PROCESS(XTEA_RTL_testbench);
    XTEA_RTL_testbench(sc_module_name name);
  };

#endif
