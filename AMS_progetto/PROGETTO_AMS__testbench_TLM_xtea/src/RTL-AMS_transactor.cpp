#include "RTL-AMS_transactor.hpp"

RTL_TO_TDF::RTL_TO_TDF(sc_core::sc_module_name):
threshold_AMS("threshold_AMS"),
command_AMS("command_AMS"),
threshold_rtl("threshold_rtl"),
word0_rtl("word0_rtl"),
word1_rtl("word1_rtl")
{}

void RTL_TO_TDF::processing()
{
    threshold_AMS.write(threshold_rtl.read());
    command_AMS.write(word0_rtl.read()*2+word1_rtl.read());
}

void RTL_TO_TDF::set_attribute()
{}