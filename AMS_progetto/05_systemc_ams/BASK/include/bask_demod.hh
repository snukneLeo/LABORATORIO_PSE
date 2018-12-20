#ifndef BASK_DEMOD_HH
#define BASK_DEMOD_HH

#include "systemc-ams.h"
#include "rectifier.hh"
#include "sampler.hh"
#include "ltf_nd_filter.hh"

class bask_demod : public sc_core::sc_module
{

    public:
        sca_tdf::sca_in< double > in;
        sca_tdf::sca_out< bool > out;

        rectifier rc;
        ltf_nd_filter lp;
        sampler sp;

        bask_demod( sc_core::sc_module_name );

    private:
        sca_tdf::sca_signal< double > rc_out, lp_out;
};

#endif
