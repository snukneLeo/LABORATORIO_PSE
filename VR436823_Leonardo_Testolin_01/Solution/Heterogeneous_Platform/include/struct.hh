#ifndef __STRUCT_LT_h__
#define __STRUCT_LT_h__

#include <systemc.h>

struct valvola_s 
{
  double tresholding;
  //xtea
  sc_uint<32> word0;
  sc_uint<32> word1;
  sc_uint<32> key0;
  sc_uint<32> key1;
  sc_uint<32> key2;
  sc_uint<32> key3;

};

struct waterTank
{
    double waterLevel;
};

#define ADDRESS_TYPE int
#define DATA_TYPE iostruct

#endif
