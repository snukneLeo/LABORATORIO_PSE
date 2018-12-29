#include "AMS-RTL_transactor.hpp"


AMS_TO_RTL::AMS_TO_RTL( sc_core::sc_module_name ) :
  waterTankLevelInput_ams("waterTankLevelInput_ams"),
  waterLevelOutput_rtl("waterLevelOutput_rtl")
{
}


void AMS_TO_RTL::processing()
{
    //ciò che vogliamo fare
    waterLevelOutput_rtl.write(waterTankLevelInput_ams.read());
}

void AMS_TO_RTL::set_attribute()
{ 
  //NULL
}
