#ifndef SAMPLER_HH
#define SAMPLER_HH

#include "systemc-ams.h"

class sampler : public sca_tdf::sca_module
{
    public:
        sca_tdf::sca_in< double > in;
        sca_tdf::sca_out< bool > out;

        sampler( sc_core::sc_module_name );

        void set_attributes();

        void processing();

    private:
        unsigned long rate;
        double threshold;
        unsigned long sample_pos;

};

#endif
