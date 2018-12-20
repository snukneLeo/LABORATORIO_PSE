#ifndef __define_LT_h__
#define __define_LT_h__

#include <systemc.h>

struct iostruct {
  sc_uint<32> datain;
  sc_uint<32> result;
};

#define ADDRESS_TYPE int
#define DATA_TYPE iostruct

#endif
