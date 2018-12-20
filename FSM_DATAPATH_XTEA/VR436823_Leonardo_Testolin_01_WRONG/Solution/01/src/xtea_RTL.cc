#include "xtea_RTL.hh"

/*xtea_RTL_main::xtea_RTL_main( sc_core::sc_module_name module_name ) :
    sc_module(module_name),
    din_rdy("din_rdy"),
    word0("word0"),
    word1("word1"),
    key0("key0"),
    key1("key1"),
    key2("key2"),
    key3("key3"),
    mode("mode"),
    result0("result0"),
    result1("result1"),
    dout_rdy("dout_rdy"),
    rst("rst"),
    clk("clock")
{
    SC_METHOD(datapath);
    //segnale a 1 faccio il reset 0 non faccio nulla
    sensitive << rst.pos();
    //sul fronte di salita acquisisco i dati
    sensitive << clk.pos();

    SC_METHOD(fsm);
    sensitive << STATUS << din_rdy << word0 << word1;

}*/

xtea_RTL::~xtea_RTL()
{
}

void xtea_RTL::datapath(void){
    if (rst.read() == 1) //fronte positivo
    {
        STATUS = ST_RESET;
    }
    else if (clk.read() == 1) //fronte di salita faccio le operazioni
    {
        STATUS = NEXT_STATUS;

        switch(STATUS)
        {
        case ST_RESET:
            dout_rdy.write(0);
            result0.write(0);
            result1.write(0);
            sum.write(0);
            delta.write(0);
            v0.write(0);
            v1.write(0);
            counter.write(0);
            temp.write(0);
            break;
        case ST_NULL0:
            //NULL
            break;
        case ST_MODE01:
            if (rst.read() == 1)
            {
                dout_rdy.write(0);
                result0.write(0);
                result1.write(0);
                sum.write(0);
                delta.write(0);
                v0.write(0);
                v1.write(0);
                counter.write(0);
                temp.write(0);
            }
            delta.write(0x9e3779b9);
            v0.write(word0.read());
            v1.write(word1.read());
            break;
        case ST_NULL1:
            break;
        case ST_SUM:
            if (rst.read() == 1)
            {
                dout_rdy.write(0);
                result0.write(0);
                result1.write(0);
                sum.write(0);
                delta.write(0);
                v0.write(0);
                v1.write(0);
                counter.write(0);
                temp.write(0);
            }
            sum.write(delta.read() * 32);
            break;
        case ST_NULL2:
            break;
        case ST_FOR00:
            if (rst.read() == 1)
            {
                dout_rdy.write(0);
                result0.write(0);
                result1.write(0);
                sum.write(0);
                delta.write(0);
                v0.write(0);
                v1.write(0);
                counter.write(0);
                temp.write(0);
            }
            if (mode.read() == 0)
            {
                if((sum.read() & 3) == 0)
                    temp.write(key0.read());
                else if((sum.read() & 3) == 1)
                    temp.write(key1.read());
                else if((sum.read() & 3) == 2)
                    temp.write(key2.read());
                else
                    temp.write(key3.read());
            }
            else
            {
                if(((sum.read() >> 11) & 3) == 0)
                    temp.write(key0.read());
                else if(((sum.read() >> 11) & 3) == 1) 
                    temp.write(key1.read());
                else if (((sum.read() >> 11) & 3) == 2)
                    temp.write(key2.read()); 
                else temp.write(key3.read());               
            }
            break;
        case ST_NULL3:
            break;
        case ST_FOR01:
            if (rst.read() == 1)
            {
                dout_rdy.write(0);
                result0.write(0);
                result1.write(0);
                sum.write(0);
                delta.write(0);
                v0.write(0);
                v1.write(0);
                counter.write(0);
                temp.write(0);
            }
                if (mode.read() == 0)
                {
                    v0.write(v0.read() + ((((v1.read() << 4) ^ (v1.read() >> 5)) + v1.read()) ^ (sum.read() + temp.read())));
                    sum.write(sum.read() + delta.read());
                }
                else
                {
                    v1.write((v1.read() - (((v0.read() << 4) ^ (v0.read() >> 5)) + v0.read()) ^ (sum.read() + temp.read())));
                    sum.write(sum.read() - delta.read());
                }
            break;
        case ST_NULL4:
            break;
        case ST_FOR02:
        if (rst.read() == 1)
            {
                dout_rdy.write(0);
                result0.write(0);
                result1.write(0);
                sum.write(0);
                delta.write(0);
                v0.write(0);
                v1.write(0);
                counter.write(0);
                temp.write(0);
            }
            if (mode.read() == 0)
            {
                if(((sum.read() >> 11) & 3) == 0)
                    temp.write(key0.read());
                else if(((sum.read() >> 11) & 3) == 1) 
                    temp.write(key1.read());
                else if (((sum.read() >> 11) & 3) == 2)
                    temp.write(key2.read()); 
                else temp.write(key3.read());
            }
            else
            {
                if((sum.read() & 3) == 0)
                    temp.write(key0.read());
                else if((sum.read() & 3) == 1)
                    temp.write(key1.read());
                else if((sum.read() & 3) == 2)
                    temp.write(key2.read());
                else
                    temp.write(key3.read());
            }
            break;
        case ST_NULL5:
            break;
        case ST_FOR03:
        if (rst.read() == 1)
            {
                dout_rdy.write(0);
                result0.write(0);
                result1.write(0);
                sum.write(0);
                delta.write(0);
                v0.write(0);
                v1.write(0);
                counter.write(0);
                temp.write(0);
            }
            if (mode.read() == 0)
            {
                v1.write((v1.read() + (((v0.read() << 4) ^ (v0.read() >> 5)) + v0.read()) ^ (sum.read() + temp.read())));
                counter.write(counter.read() + 1);
            }
            else
            {
                v0.write(v0.read() - ((((v1.read() << 4) ^ (v1.read() >> 5)) + v1.read()) ^ (sum.read() + temp.read())));
                counter.write(counter.read() + 1);
            }
            break;
        case ST_NULL6:
            break;
        case ST_FINALE:
        if (rst.read() == 1)
            {
                dout_rdy.write(0);
                result0.write(0);
                result1.write(0);
                sum.write(0);
                delta.write(0);
                v0.write(0);
                v1.write(0);
                counter.write(0);
                temp.write(0);
            }
            result0.write(v0.read());
            result1.write(v1.read());
            break;
        case ST_FINALE01:
            dout_rdy.write(1);
            if (rst.read() == 1)
            {
                dout_rdy.write(0);
                result0.write(0);
                result1.write(0);
                sum.write(0);
                delta.write(0);
                v0.write(0);
                v1.write(0);
                counter.write(0);
                temp.write(0);
            }
            //cout << "result0" << result0.read() << endl;
            //cout << "result1" << result1.read() << endl;
            break;
        } 
    }
}


void xtea_RTL::fsm(void)
{
    NEXT_STATUS = STATUS;

    switch(STATUS)
    {
        case ST_RESET:
            NEXT_STATUS = ST_NULL0;
            break;

        case ST_NULL0:
            if (din_rdy.read() == 0)
            {
                NEXT_STATUS = ST_NULL0;
            }
            else
            {   
                NEXT_STATUS = ST_MODE01;
            }
            break;
        case ST_MODE01:
            NEXT_STATUS = ST_NULL1;
            break;
        case ST_NULL1:
            NEXT_STATUS = ST_SUM;
            break;
        case ST_SUM:
            NEXT_STATUS = ST_NULL2;
            break;
        case ST_NULL2:
            NEXT_STATUS = ST_FOR00;
            break;
        case ST_FOR00:
            NEXT_STATUS = ST_NULL3;
            break;
        case ST_NULL3:
            NEXT_STATUS = ST_FOR01;
            break;
        case ST_FOR01:
            NEXT_STATUS = ST_NULL4;
            break;
        case ST_NULL4:
            NEXT_STATUS = ST_FOR02;
            break;
        case ST_FOR02:
            NEXT_STATUS = ST_NULL5;
            break;
        case ST_NULL5:
            NEXT_STATUS = ST_FOR03;
            break;
        case ST_FOR03:
            NEXT_STATUS = ST_NULL6;
            break;
        case ST_NULL6:
            if (counter.read() < 32)
            {
                NEXT_STATUS = ST_FOR00;
            }
            else
            {
                NEXT_STATUS = ST_FINALE;
            }
            //cout << "FSM - COUNTER: " << counter.read() << endl;
            break;
        case ST_FINALE:
            NEXT_STATUS = ST_FINALE01;
            break;
        case ST_FINALE01:
            NEXT_STATUS = ST_FINALE01;
            break;
    }
}
