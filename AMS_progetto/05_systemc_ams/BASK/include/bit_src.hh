#ifndef BIT_SRC_HH
#define BIT_SRC_HH

#include "systemc.h"
#include "systemc-ams.h"

class bit_src : public sca_tdf::sca_module
{

    public:
        sca_tdf::sca_out< bool > out; //out port

        bit_src( sc_core::sc_module_name );

        void processing();
};

#endif
