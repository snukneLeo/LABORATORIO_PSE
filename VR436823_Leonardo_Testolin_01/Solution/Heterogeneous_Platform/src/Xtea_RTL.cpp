#include "Xtea_RTL.hpp"

//definizione della macchina a stati finiti e la sua evoluzione
void XTEA_RTL::fsm()
{
    NEXT_STATUS = STATUS;
    switch (STATUS)
    {
    case INIZIO:
        NEXT_STATUS = INITIAL;
        break;
    case INITIAL:
        if (din_rdy.read() == 1)
        {
            NEXT_STATUS = CHIAVI_WORD0;
        }
        else
            NEXT_STATUS = INITIAL;
        break;
    case CHIAVI_WORD0:
        if (mode.read() == 0)
            NEXT_STATUS = CRIPTAZIONE_1;
        else if (mode.read() == 1)
            NEXT_STATUS = SOMMA_DEC;
        break;
    case CRIPTAZIONE_1:
        NEXT_STATUS = CRIPTAZIONE_2;
        break;
    case CRIPTAZIONE_2:
        if (contatore.read() == 31)
            NEXT_STATUS = COMPUTAZIONE_TEMINATA;
        else
            NEXT_STATUS = CRIPTAZIONE_1;
        break;
    case SOMMA_DEC:
        NEXT_STATUS = DECRIPTAZIONE_1;
        break;
    case DECRIPTAZIONE_1:
        NEXT_STATUS = DECRIPTAZIONE_2;
        break;
    case DECRIPTAZIONE_2:
        if (contatore.read() == 31)
            NEXT_STATUS = COMPUTAZIONE_TEMINATA;
        else
            NEXT_STATUS = DECRIPTAZIONE_1;
        break;
    case COMPUTAZIONE_TEMINATA:
        NEXT_STATUS = INITIAL;
        break;
    }
}
//definzione del datapath
void XTEA_RTL::datapath()
{
    if (reset.read() == 1)
    {
        STATUS = INIZIO;
    }
    else if (clk.read() == 1)
    {
        STATUS = NEXT_STATUS;
        switch (STATUS)
        {
        case INIZIO:
            dout_rdy.write(0);
            out0.write(0);
            out1.write(0);
            delta.write(0x9e3779b9);
            word0_tmp.write(0);
            word1_tmp.write(0);
            break;
        case INITIAL:
            dout_rdy.write(0);
            somma.write(0);
            contatore.write(0);
            word0_tmp.write(0);
            word1_tmp.write(0);
            break;
        case CHIAVI_WORD0:
            word0_tmp.write(word0.read());
            word1_tmp.write(word1.read());
            k1.write(key1.read());
            k2.write(key2.read());
            k3.write(key3.read());
            k4.write(key4.read());
            break;
        //criptazione prima parte
        case CRIPTAZIONE_1:
            crip1();
            break;
        //criptazione seconda parte
        case CRIPTAZIONE_2:
            crip2();
            break;
        case SOMMA_DEC:
            somma.write(delta.read() * 32);
            break;
        //decriptazione prima parte
        case DECRIPTAZIONE_1:
            decript1();
            break;
        //decriptazione seconda parte
        case DECRIPTAZIONE_2:
            decript2();
            break;
        case COMPUTAZIONE_TEMINATA:
            out0.write(word0_tmp.read());
            out1.write(word1_tmp.read());
            dout_rdy.write(1);
            break;
        }
    }
}


void XTEA_RTL::crip1()
{
    if ((somma.read() & 3) == 0)
                word0_tmp.write(word0_tmp.read() + ((((word1_tmp.read() << 4) ^ (word1_tmp.read() >> 5)) +
                                           word1_tmp.read()) ^
                                          (somma.read() + k1.read())));
            else if ((somma.read() & 3) == 1)
                word0_tmp.write(word0_tmp.read() + (((((word1_tmp.read() << 4) ^ (word1_tmp.read() >> 5)) +
                                            word1_tmp.read()) ^
                                           (somma.read() + k2.read()))));
            else if ((somma.read() & 3) == 2)
                word0_tmp.write(word0_tmp.read() + ((((word1_tmp.read() << 4) ^ (word1_tmp.read() >> 5)) +
                                           word1_tmp.read()) ^
                                          (somma.read() + k3.read())));
            else
                word0_tmp.write(word0_tmp.read() + ((((word1_tmp.read() << 4) ^ (word1_tmp.read() >> 5)) +
                                           word1_tmp.read()) ^
                                          (somma.read() + k4.read())));
            somma.write(somma.read() + delta.read());
}

void XTEA_RTL::crip2()
{
    if ((somma.read() >> 11 & 3) == 0)
                word1_tmp.write(word1_tmp.read() + ((((word0_tmp.read() << 4) ^ (word0_tmp.read() >> 5)) +
                                           word0_tmp.read()) ^
                                          (somma.read() + k1.read())));
            else if ((somma.read() >> 11 & 3) == 1)
                word1_tmp.write(word1_tmp.read() + (((((word0_tmp.read() << 4) ^ (word0_tmp.read() >> 5)) +
                                            word0_tmp.read()) ^
                                           (somma.read() + k2.read()))));
            else if ((somma.read() >> 11 & 3) == 2)
                word1_tmp.write(word1_tmp.read() + ((((word0_tmp.read() << 4) ^ (word0_tmp.read() >> 5)) +
                                           word0_tmp.read()) ^
                                          (somma.read() + k3.read())));
            else
                word1_tmp.write(word1_tmp.read() + ((((word0_tmp.read() << 4) ^ (word0_tmp.read() >> 5)) +
                                           word0_tmp.read()) ^
                                          (somma.read() + k4.read())));
            contatore.write(contatore.read() + 1);
}

void XTEA_RTL::decript1()
{
    if ((somma.read() >> 11 & 3) == 0)
                word1_tmp.write(word1_tmp.read() - ((((word0_tmp.read() << 4) ^ (word0_tmp.read() >> 5)) +
                                           word0_tmp.read()) ^
                                          (somma.read() + k1.read())));
            else if ((somma.read() >> 11 & 3) == 1)
                word1_tmp.write(word1_tmp.read() - (((((word0_tmp.read() << 4) ^ (word0_tmp.read() >> 5)) +
                                            word0_tmp.read()) ^
                                           (somma.read() + k2.read()))));
            else if ((somma.read() >> 11 & 3) == 2)
                word1_tmp.write(word1_tmp.read() - ((((word0_tmp.read() << 4) ^ (word0_tmp.read() >> 5)) +
                                           word0_tmp.read()) ^
                                          (somma.read() + k3.read())));
            else
                word1_tmp.write(word1_tmp.read() - ((((word0_tmp.read() << 4) ^ (word0_tmp.read() >> 5)) +
                                           word0_tmp.read()) ^
                                          (somma.read() + k4.read())));
            somma.write(somma.read() - delta.read());
}

void XTEA_RTL::decript2()
{
    if ((somma.read() & 3) == 0)
                word0_tmp.write(word0_tmp.read() - ((((word1_tmp.read() << 4) ^ (word1_tmp.read() >> 5)) +
                                           word1_tmp.read()) ^
                                          (somma.read() + k1.read())));
            else if ((somma.read() & 3) == 1)
                word0_tmp.write(word0_tmp.read() - ((((word1_tmp.read() << 4) ^ (word1_tmp.read() >> 5)) +
                                           word1_tmp.read()) ^
                                          (somma.read() + k2.read())));
            else if ((somma.read() & 3) == 2)
                word0_tmp.write(word0_tmp.read() - ((((word1_tmp.read() << 4) ^ (word1_tmp.read() >> 5)) +
                                           word1_tmp.read()) ^
                                          (somma.read() + k3.read())));
            else
                word0_tmp.write(word0_tmp.read() - ((((word1_tmp.read() << 4) ^ (word1_tmp.read() >> 5)) +
                                           word1_tmp.read()) ^
                                          (somma.read() + k4.read())));
            contatore.write(contatore.read() + 1);
}