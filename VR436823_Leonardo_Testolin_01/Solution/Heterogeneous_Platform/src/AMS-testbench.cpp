#include "AMS-testbench.hpp"
//costruttore
AMS_testbench::AMS_testbench(sc_core::sc_module_name) : controller("controller", 0x6a1d78c8, 0x8c86d67f, 0x2a65bfbe, 0xb4bd6e46, 0x9e3779b9),
    tlm_to_rtl("tlm_to_rtl"),
    xtea("Xtea"),
    rtl_to_ams("rtl_to_ams"),
    valve("valve"),
    tank("tank"),
    ams_to_rtl("ams_to_rtl"),
    rtl_to_tlm("rtl_to_tlm")
{
    //collegameto dei segnali con i diversi moduli
    clock_out(clock);

    //da controller a transattore tlm-rtl
    controller.initiator_socket(tlm_to_rtl.target_socket);
    tlm_to_rtl.word0(word0_rt);
    tlm_to_rtl.word1(word1_rt);
    tlm_to_rtl.key1(key0);
    tlm_to_rtl.key2(key1);
    tlm_to_rtl.key3(key2);
    tlm_to_rtl.key4(key3);
    tlm_to_rtl.mode(mode);
    tlm_to_rtl.threshold(threshold_rt);
    tlm_to_rtl.reset(reset);
    tlm_to_rtl.din_rdy(din);
    tlm_to_rtl.clock(clock);

    //da transattore tlm-rtl a xtea
    xtea.word0(word0_rt);
    xtea.word1(word1_rt);
    xtea.key1(key0);
    xtea.key3(key2);
    xtea.key2(key1);
    xtea.key4(key3);
    xtea.mode(mode);
    xtea.reset(reset);
    xtea.din_rdy(din);
    xtea.clk(clock);
    xtea.out0(word0_dec_rt);
    xtea.out1(word1_dec_rt);
    xtea.dout_rdy(dout);

    //da transattore tlm-rtl a transattore rtl-ams
    rtl_to_ams.word0_rtl(word0_dec_rt);
    rtl_to_ams.word1_rtl(word1_dec_rt);
    rtl_to_ams.dout(dout);
    rtl_to_ams.threshold_rtl(threshold_rt);
    rtl_to_ams.command_ams(command_ams);
    rtl_to_ams.threshold_ams(threshold_ams);

    //da transattore rtl-ams a valvola
    valve.thresholding(threshold_ams);
    valve.command(command_ams);
    valve.current_aperture(aperture);
    //da valvola a watertank
    tank.in(aperture);
    tank.out(water_level_ams);

    //da watertank a transattore ams-rtl
    ams_to_rtl.water_level_ams(water_level_ams);
    ams_to_rtl.water_level_rtl(water_level_rt);

    //da transattore ams-rtl a transattore rtl-tlm
    rtl_to_tlm.water_level_rt(water_level_rt);
    rtl_to_tlm.initiator_socket(controller.target_socket);

    SC_THREAD(clock_gen);
}

//gestine del clock
void AMS_testbench::clock_gen()
{
    while (true)
    {
        clock_out.write(SC_LOGIC_1);
        wait(PERIOD / 2, SC_US);
        clock_out.write(SC_LOGIC_0);
        wait(PERIOD / 2, SC_US);
    }
}