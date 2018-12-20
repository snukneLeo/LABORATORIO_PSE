#ifndef __define_UT_h__
#define __define_UT_h__

#include <systemc.h>

struct iostruct {
  sc_int<32> datain;
  sc_int<32> result;
};

#define ADDRESS_TYPE int
#define DATA_TYPE iostruct

#endif
