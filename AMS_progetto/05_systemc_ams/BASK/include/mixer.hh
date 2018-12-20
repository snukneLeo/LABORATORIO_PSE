#ifndef MIXER_HH
#define MIXER_HH

#include "systemc.h"
#include "systemc-ams.h"

SCA_TDF_MODULE( mixer )
{
    sca_tdf::sca_in< bool > in_bin; //input port baseband signal
    sca_tdf::sca_in< double > in_wav; //input port carrier signal
    sca_tdf::sca_out< double > out; //output port modulated signal

    SCA_CTOR( mixer )
        : in_bin("in_bin"), in_wav("in_wav"), out("out"), rate(40){} 
    // use a carrier data rate of 40

    void set_attributes();

    void processing();

    private:
    unsigned long rate;

};


#endif
