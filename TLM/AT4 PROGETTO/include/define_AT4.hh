#ifndef __define_AT4_h__
#define __define_AT4_h__

#include <systemc.h>

struct iostruct {
  sc_uint<32> word0;
  sc_uint<32> word1;
  sc_uint<32> result0;
  sc_uint<32> result1;
  sc_uint<32> key0;
  sc_uint<32> key1;
  sc_uint<32> key2;
  sc_uint<32> key3;
  bool mode;
};

#define ADDRESS_TYPE int
#define DATA_TYPE iostruct

#endif
