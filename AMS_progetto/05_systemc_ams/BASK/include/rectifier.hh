#ifndef RECTIFIER_HH
#define RECTIFIER_HH

#include "systemc.h"
#include "systemc-ams.h"

class rectifier : public sca_tdf::sca_module
{
    public:
        sca_tdf::sca_in< double > in;
        sca_tdf::sca_out< double > out;

        rectifier( sc_core::sc_module_name );

        void processing();
};

#endif
