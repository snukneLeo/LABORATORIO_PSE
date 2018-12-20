#ifndef CONTROLLER_TDF_HH
#define CONTROLLER_TDF_HH
#define REAL

#include "systemc-ams.h"
#include "params.hh"

extern double reference[500];

SCA_TDF_MODULE( controller )
{
  public:
    sca_tdf::sca_in< double > in;
    sca_tdf::sca_out< double > out;

    controller( sc_core::sc_module_name );
    ~controller();

    void set_attributes();
    void ac_processing();
    void processing();

  private:
    double Ts;
    double prev;
    double prev_err;
    double ref;

#ifdef TRACING
    FILE * log_error;
    FILE * log_reference;
#endif

#ifdef REAL
    int s;
#endif

 





};



#endif //CONTROLLER_TDF_HH

