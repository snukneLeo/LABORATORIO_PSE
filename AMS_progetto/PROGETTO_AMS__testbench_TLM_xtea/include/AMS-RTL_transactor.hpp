#ifndef transattore_from_AMS_to_RTL_HH
#define transattore_from_AMS_to_RTL_HH

#include "systemc-ams.h"

SCA_TDF_MODULE( AMS_TO_RTL )
{
    public:
        //ingresso
        sca_tdf::sca_in< double > waterTankLevelInput_ams;
        sca_tdf::sca_de::sca_out< double > waterLevelOutput_rtl;

        AMS_TO_RTL( sc_core::sc_module_name );
        
        void set_attribute();
        void processing();

};

#endif //CONTROLLER_IFACE_HH
