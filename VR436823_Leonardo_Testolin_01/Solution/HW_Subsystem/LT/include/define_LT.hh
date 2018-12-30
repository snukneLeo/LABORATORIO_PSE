#ifndef __define_UT_h__
#define __define_UT_h__

#include <systemc.h>

//definizione struttura per il payload
struct iostruct 
{
  //definzione di parole, chiavi, e risultati
  sc_uint<32> word0;
  sc_uint<32> word1;
  sc_uint<32> result0;
  sc_uint<32> result1;
  sc_uint<32> key0;
  sc_uint<32> key1;
  sc_uint<32> key2;
  sc_uint<32> key3;
  bool mode; //modalità tra cript e decript
};
#endif
