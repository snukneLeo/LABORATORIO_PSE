#ifndef xtea_RTL_H
#define xtea_RTL_H

#include "systemc.h"

// classe xtea_RTL deriva da sc_module
class xtea_RTL : public sc_core::sc_module
{

    public:

        sc_in<bool>           rst;
        sc_in< sc_logic > clk;

        sc_in<sc_uint<1> >    din_rdy;
        sc_in<sc_uint<32> >   word0;
        sc_in<bool>           mode;
        sc_in<sc_uint<32> >   word1;
        sc_in<sc_uint<32> >   key0;
        sc_in<sc_uint<32> >   key1;
        sc_in<sc_uint<32> >   key2;
        sc_in<sc_uint<32> >   key3;
       


        sc_out<sc_uint<32> >  result0;
        sc_out<sc_uint<32> >  result1;
        sc_out<sc_uint<1> >   dout_rdy;
        

        // macro che indica il metodo che inizializza i processi che diventano processi o thread
        //SC_HAS_PROCESS(xtea_RTL);

        //xtea_RTL( sc_core::sc_module_name module_name );
         // distruttore della classe, es c++ delete 
        ~xtea_RTL();
        SC_CTOR(xtea_RTL){
            SC_METHOD(datapath);
            sensitive << rst.pos();
            sensitive << clk.pos();

            SC_METHOD(fsm);
            sensitive << STATUS << din_rdy;
        };


        // costruttore (fa quello che ho commentato su xtea_RTL.cc)

    protected:
        typedef enum {ST_RESET,
                      ST_NULL0,
                      ST_MODE01,
                      ST_NULL1,
                      ST_FOR00,
                      ST_FOR01,
                      ST_NULL2,
                      ST_NULL3,
                      ST_NULL4,
                      ST_SUM,
                      ST_FOR02,
                      ST_NULL5,
                      ST_FOR03,
                      ST_NULL6,
                      ST_FINALE,
                      ST_FINALE01
                                } 
                      STATES;

        sc_signal<STATES> STATUS, NEXT_STATUS;
        sc_signal<sc_uint<64> > sum;
        sc_signal<sc_uint<32> > delta,v0,v1,temp,counter;
        
        void fsm(void);
        void datapath(void);

};

#endif
