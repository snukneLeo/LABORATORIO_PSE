#ifndef XTEA_XTEA_RTL_TESTBENCH_H
#define XTEA_XTEA_RTL_TESTBENCH_H

#include <systemc.h>

SC_MODULE(XTEA_RTL_testbench) {
private:
  void run();

public:
  sc_in_clk clk;    // The clock signal
  sc_out<bool> rst; // The reset signal

  sc_out<sc_uint<32> > word0; // 32-bit data input ports
  sc_out<sc_uint<32> > word1;
  sc_out<sc_uint<32> > key_i0;  // 32-bit key input ports
  sc_out<sc_uint<32> > key_i1;
  sc_out<sc_uint<32> > key_i2;
  sc_out<sc_uint<32> > key_i3;

  // 32-bit output ports
  sc_in<sc_uint<32> > out0;
  sc_in<sc_uint<32> > out1;
  sc_in<bool> dout_rdy;

  sc_out<bool> input_ready; // Flag for telling system is ready
  sc_out<sc_uint<1> > mode; // Flag for setting encryption/decryption mode (0=encrypt,
                     // 1=decrypt)

  SC_HAS_PROCESS(XTEA_RTL_testbench);

  XTEA_RTL_testbench(sc_module_name name);
};

#endif // XTEA_XTEA_RTL_TESTBENCH_H
