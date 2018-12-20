#ifndef BASK_MOD_HH
#define BASK_MOD_HH

#include "systemc.h"
#include "systemc-ams.h"

#include "mixer.hh"
#include "sin_src.hh"

SC_MODULE( bask_mod )
{
    public:
        sca_tdf::sca_in< bool > in;
        sca_tdf::sca_out< double > out;

        sin_src sine;
        mixer mix;

        bask_mod( sc_core::sc_module_name );

    private:

        sca_tdf::sca_signal< double > carrier;  

};

#endif
