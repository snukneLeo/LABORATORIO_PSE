#ifndef XTEA_XTEA_RTL_H
#define XTEA_XTEA_RTL_H

#include <systemc.h>

SC_MODULE(XTEA_RTL) {
  sc_in<sc_logic > clk;   // The clock signal
  sc_in<bool> rst; // The reset signal

  sc_in<sc_uint<32> > word0; // 32-bit data input ports
  sc_in<sc_uint<32> > word1;
  sc_in<sc_uint<32> > key_i0;
  sc_in<sc_uint<32> > key_i1;
  sc_in<sc_uint<32> > key_i2;  // 32-bit key input ports
  sc_in<sc_uint<32> > key_i3;

  sc_out<sc_uint<32> > out0; // 32-bit output ports
  sc_out<sc_uint<32> > out1;
  sc_in<bool> input_ready; // Flag for telling system is ready
  sc_in<sc_uint<1> > mode; // Flag for setting encryption/decryption mode (0=encrypt,
                    // 1=decrypt)

  typedef enum {
    IDLE,
    BUSY
  } STATES; // Possible states of the FSM

  sc_signal<STATES> STATUS, NEXT_STATUS; // Signals for representing states
  sc_signal<sc_uint<32> > key0;
  sc_signal<sc_uint<32> > key1;
  sc_signal<sc_uint<32> > key2;  // 32-bit key input ports
  sc_signal<sc_uint<32> > key3;
  sc_out<sc_uint<32> > word0_pr;
  sc_out<sc_uint<32> > word1_pr;

  void fsm();

  void datapath();

  void xtea(sc_uint<32> word0, sc_uint<32> word1, sc_uint<32> key0,
            sc_uint<32> key1, sc_uint<32> key2, sc_uint<32> key3, sc_uint<1> mode,
            sc_uint<32> *result0, sc_uint<32> *result1);

  SC_CTOR(XTEA_RTL) {
    SC_METHOD(datapath);
    sensitive << clk.pos() << rst.pos();

    SC_METHOD(fsm);
    sensitive << STATUS << input_ready << mode;
  }
};

#endif // XTEA_XTEA_RTL_H
