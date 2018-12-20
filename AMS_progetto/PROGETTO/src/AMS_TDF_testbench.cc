#include "AMS_TDF_testbench.hh"

amsTest::amsTest( sc_core::sc_module_name):
    command("command"), thresholding("thresholding"), waterTank("waterTank")
{
    thresh = 0.7;
    samples = 0;
    counter = 0;
}

void amsTest::set_attributes()
{
    waterTank.set_timestep(5,SC_MS);
    waterTank.set_delay(1);
    samplesTowait = 1000;//numero campioni da inviare
}

void amsTest::processing() //input: idle/open/close; thresholding
{
    if(waterTank.read() >= 5 && waterTank.read() <= 8.8)
    {
        command = IDLE;
        counter = 0;
    }
    else if(waterTank.read() > 8.8 && counter == samplesTowait)
    {
        command = CLOSE;
        thresh *= 0.7;
        counter = 0;
    }
    else if(waterTank.read() < 5 && counter == samplesTowait)
    {
        command = OPEN;
        thresh *= 1.1; 
        counter = 0;
    }
    thresholding.write(thresh);
    counter++;
}