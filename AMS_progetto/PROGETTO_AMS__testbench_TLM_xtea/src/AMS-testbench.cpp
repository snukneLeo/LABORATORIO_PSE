#include "systemc.h"
#include "systemc-ams.h"
#include "RTL-AMS_transactor.hpp"
#include "TLM-RTL_transactor.hpp"
#include "Controller_TLM.hpp"
#include "AMS-RTL_transactor.hpp"
#include "RTL-TLM_transactor.hpp"
#include "Valve.hpp"
#include "Water_tank.hpp"
#include "Xtea_RTL.hpp"
#include "AMS-testbench.hpp"

testbench_AMS::testbench_AMS(sc_core::sc_module_name):
controller("TLM_controller",0x6a1d78c8, 0x8c86d67f, 0x2a65bfbe, 0xb4bd6e46, 0x9e3779b9),tlm_to_rtl("tlm_to_rtl"),xtea("xtea"),
rtl_to_tdf("rtl_to_ams"),valvola("valve"),tank("waterTank"),
ams_to_rtl("ams_to_rtl"),rtl_to_tlm("rtl_to_tlm")
{
    clock_out(clock);
    controller.initiator_socket(tlm_to_rtl.target_socket);
    tlm_to_rtl.word0(word0_rtl);
    tlm_to_rtl.word1(word1_rtl);
    tlm_to_rtl.key0(key0);
    tlm_to_rtl.key1(key1);
    tlm_to_rtl.key2(key2);
    tlm_to_rtl.key3(key3);
    tlm_to_rtl.mode(mode);
    tlm_to_rtl.threshold(thresh);
    tlm_to_rtl.reset(reset);
    tlm_to_rtl.din_rdy(din);
    tlm_to_rtl.clock(clock);

    //from tlm-rtl to xtea
    xtea.word0(word0_rtl);
    xtea.word1(word1_rtl);
    xtea.key_i0(key0);
    xtea.key_i1(key1);
    xtea.key_i2(key2);
    xtea.key_i3(key3);
    xtea.mode(mode);
    xtea.rst(reset);
    xtea.input_ready(din);
    xtea.clk(clock);
    xtea.word0_pr(word0_dec_rtl);
    xtea.word1_pr(word1_dec_rtl);

    //from tlm-rtl to rtl-ams
    rtl_to_tdf.word0_rtl(word0_dec_rtl);
    rtl_to_tdf.word1_rtl(word1_dec_rtl);
    rtl_to_tdf.threshold_rtl(thresh);
    rtl_to_tdf.threshold_AMS(thresh_ams);
    rtl_to_tdf.command_AMS(command_ams);
    //from rtl-ams to valve
    valvola.thresholding(thresh_ams);
    valvola.command(command_ams);
    valvola.current_aperture(aperture);
    //from valvola to water tank
    tank.in(aperture);
    tank.out(water_level_ams);

    //from water tank to ams-rtl
    ams_to_rtl.waterTankLevelInput_ams(water_level_ams);
    ams_to_rtl.waterLevelOutput_rtl(water_level_rtl);
    //from ams-rtl to rtl-tlm
    rtl_to_tlm.waterLevelInput_rtl(water_level_rtl);
    rtl_to_tlm.initiator_socket(controller.target_socket);

    SC_THREAD(clock_gen);
}

void testbench_AMS::clock_gen()
{
    while(true)
    {
        clock_out.write(SC_LOGIC_1);
        wait(PERIOD/2,SC_US);
        clock_out.write(SC_LOGIC_0);
        wait(PERIOD/2,SC_US);
    }
}