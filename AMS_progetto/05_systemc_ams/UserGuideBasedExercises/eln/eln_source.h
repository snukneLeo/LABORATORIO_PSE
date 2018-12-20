#ifndef ELN_SOURCE_H
#define ELN_SOURCE_H

#include <systemc-ams>

SC_MODULE(eln_source) {
    public:

        //--------------------Ports for TDF-----------------------------
        sca_tdf::sca_out<double>    out;
        sca_eln::sca_tdf::sca_vsink eln2tdf;

        //--------------------Local Declaration Here--------------------
        sca_eln::sca_vsource v_src;

        eln_source(sc_core::sc_module_name _name);

        ~eln_source();

    private:
        sca_eln::sca_node     n1;
        sca_eln::sca_node_ref gnd;
};

#endif
