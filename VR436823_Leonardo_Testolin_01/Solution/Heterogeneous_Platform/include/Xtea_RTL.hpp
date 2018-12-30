#ifndef Xtea_RTL_HPP
#define XTea_RTL_HPP

#include <systemc.h>

SC_MODULE(XTEA_RTL)
{
    public:
        //definizione dei segnali di input per il modulo
        sc_in<sc_logic > clk;
        //due segnali per le parole da criptare e decriptare
        sc_in<sc_uint<32> > word0;
        sc_in<sc_uint<32> > word1;
        //quattro chiavi usate per l'algoritmo
        sc_in<sc_uint<32> > key1;
        sc_in<sc_uint<32> > key2;
        sc_in<sc_uint<32> > key3;
        sc_in<sc_uint<32> > key4;
        //scelta della modalità dell'algoritmo
        sc_in<sc_uint<1> > mode;
        //input pronto
        sc_in<bool> din_rdy;
        //reset -> ritorno allo stato inziale
        sc_in<bool> reset;
        
        //segnali di output
        //parole criptate e decriptate
        sc_out<sc_uint<32> > out0;
        sc_out<sc_uint<32> > out1;
        //segnali di output pronto
        sc_out<bool> dout_rdy;

        //definizone del costruttore
        SC_CTOR(XTEA_RTL)
        {
            //metodo sensibile allo stato in cui si evolve e se il segnale è pronto   
            SC_METHOD(fsm);
            sensitive <<STATUS<<din_rdy;
            //metodo sensibile al clock e al reset
            SC_METHOD(datapath);
            sensitive <<clk.pos();
            sensitive<<reset.pos();
        };
        //definizone delle variabili
        sc_signal<sc_uint<5> > contatore; //contatore per i cicli "for"
        sc_signal<sc_uint<32> > word0_tmp; //i valori usati come temp
        sc_signal<sc_uint<32> > word1_tmp;
        sc_signal<sc_uint<32> > delta; //delta costante moltiplicativa dell'algoritmo
        sc_signal<sc_uint<32> > k1; //le varibili usate per le chiavi
        sc_signal<sc_uint<32> > k2;
        sc_signal<sc_uint<32> > k3;
        sc_signal<sc_uint<32> > k4;
        sc_signal<sc_uint<64> > somma; //varibile usata all'interno dell'algoritmo

        //definizione degli stati in cui la macchina FSM deve evolvere
        typedef enum 
        {
            INIZIO,
            INITIAL,
            SOMMA_DEC,
            CHIAVI_WORD0,
            CRIPTAZIONE_1,
            CRIPTAZIONE_2,
            DECRIPTAZIONE_1,
            DECRIPTAZIONE_2,
            COMPUTAZIONE_TEMINATA
        } STATES;

        //definizone di un segnale che contiene gli stati possibili
        sc_signal<int> STATUS, NEXT_STATUS;
        //definizione metodi
        void fsm();
        void datapath();
        void crip1();
        void crip2();
        void decript1();
        void decript2();
};
#endif