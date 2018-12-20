#ifndef root_RTL_H
#define root_RTL_H

#include "systemc.h"

SC_MODULE(root_RTL){

  sc_in<sc_uint<1> >    number_isready;
  sc_in<sc_uint<32> >   number_port;
  sc_out<sc_uint<32> >  result_port;
  sc_out<sc_uint<1> >   result_isready;
  sc_in<bool>           reset;
  sc_in< sc_dt::sc_logic > clk;

  typedef enum {Reset_ST, ST_0, ST_1, ST_2, ST_3, ST_4} STATES;

  sc_signal<STATES> STATUS, NEXT_STATUS;
  sc_signal<sc_uint<32> > Rem;
  sc_signal<sc_uint<32> > Root;
  sc_signal<sc_uint<32> > Number;
  sc_signal<sc_uint<5> >  Counter;

  void elaborate_SQRT(void);
  void elaborate_SQRT_FSM(void);

  SC_CTOR(root_RTL){
    SC_METHOD(elaborate_SQRT_FSM);
    sensitive << reset.neg();
    sensitive << clk.pos();

     

    SC_METHOD(elaborate_SQRT);
    sensitive << STATUS << number_isready << number_port << Counter;
  };
};

#endif
