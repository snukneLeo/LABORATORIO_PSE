#include "AMS_TDF_testbench.hh"

//costrutore e inizializzazione dei valori inziali
amsTest::amsTest( sc_core::sc_module_name):
    command("command"), thresholding("thresholding"), waterTank("waterTank")
{
    thresh = 0.7; //dettato dalle specifiche
    samples = 0;
    counter = 0;
}

//funzione per indicare ritardi e i temp step
void amsTest::set_attributes()
{
    waterTank.set_timestep(5,SC_MS); //set il tempo di attesa
    waterTank.set_delay(1); //ritardo
    samplesTowait = 1000;//numero campioni da inviare
}

void amsTest::processing() //input: idle/open/close; thresholding
{
    //controllo del livello dell'acqua e di conseguenza l'invio del comando e della thresh
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
    counter++; //attesa dei campioni
}