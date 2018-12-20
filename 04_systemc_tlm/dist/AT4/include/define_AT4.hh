#ifndef __define_AT4_h__
#define __define_AT4_h__

#include <systemc.h>

// payload data struct declaration
struct iostruct {
  sc_uint<32> datain;
  bool mode;
  sc_uint<32> address;
  sc_uint<32> result;
};

// constant declarations
#define ADDRESS_TYPE int
#define DATA_TYPE iostruct
#define WRITE_MODE 0
#define DB_MODE 1
#define THRESHOLD 500

#endif
