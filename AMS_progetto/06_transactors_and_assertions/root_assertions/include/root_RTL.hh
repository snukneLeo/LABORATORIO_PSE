#ifndef root_RTL_H
#define root_RTL_H

#include "systemc.h"

SC_MODULE(root_RTL){

  sc_in<sc_uint<1> >    din_rdy;
  sc_in<sc_uint<32> >   din;
  sc_out<sc_uint<32> >  dout;
  sc_out<sc_uint<1> >   dout_rdy;
  sc_in<bool>           rst;
  sc_in< sc_dt::sc_logic > clk;

  typedef enum {Reset_ST, ST_0, ST_1, ST_2, ST_3, ST_4} STATES;

  sc_signal<STATES> STATUS, NEXT_STATUS;
  sc_signal<sc_uint<32> > Rem;
  sc_signal<sc_uint<32> > Root;
  sc_signal<sc_uint<32> > Number;
  sc_signal<sc_uint<5> >  Counter;

  // CHECKERS

  void property1(void);
  // if din_rdy == 1 then dout_rdy == 1 
  // in less than 100 clock cycles

  void property2(void);
  // if din_rdy == 0 then dout == 0 and dout_rdy == 0

  void property4(void);
  // if Counter < 16 then STATUS = ST4

  void fsm(void);
  void datapath(void);

  SC_CTOR(root_RTL){
    SC_METHOD(datapath);
    sensitive << rst.neg();
    sensitive << clk.pos();



    SC_METHOD(fsm);
    sensitive << STATUS << din_rdy << din << Counter;

    SC_THREAD(property1);
    sensitive << clk.pos();

    SC_THREAD(property2);
    sensitive<<din_rdy<<dout<<dout_rdy;

    SC_THREAD(property4);
    sensitive<<Counter<<STATUS;

  };
};

#endif
