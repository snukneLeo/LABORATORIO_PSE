#include "Valve.hpp"

Valve::Valve( sc_core::sc_module_name):
    command("command"), thresholding("thresholding"), current_aperture("current_aperture")
{
    current_valve = 0;
}

void Valve::set_attributes()
{
    command.set_timestep(5,SC_MS);
    command.set_delay(1);
    thresholding.set_timestep(5,SC_MS);
    thresholding.set_delay(1);
}

//come collegare il segnale di ingresso alla valvola
//e come fare l'uscita della valvola
void Valve::processing() //input: idle/open/close; thresholding
{
    //equazione integrante per l'apertura
    double delta = 0.25*get_timestep().to_seconds();
    if (command.read() == IDLE) //a = 0
    {
        //scrittura dell'apertura invariata
        current_aperture.write(current_valve);
    }
    else if(command.read() == OPEN) // a = 0.25
    {
        //se il valore dell'acqua è maggiore della thresh allora il valore corrente lo salvo 
        //come thresh e poi faccio uscire l'apertura della thresh
        if(current_valve > thresholding.read())
        {
            current_valve = thresholding.read();
            current_aperture.write(thresholding.read());
        }
        //altimenti posso aggiungere ciò che chiede l'apertura
        else
        {
            current_valve += delta;
            current_aperture.write(current_valve);
        } 
    }
    //se sono sopra la soglia allora chiudo l'apertura
    else if(command.read() == CLOSE) // a = -0.25
    {
        if(current_valve<0)
        {
            current_valve = thresholding.read();
            current_aperture.write(0);
        }
        else
        {
            current_valve -= delta;
            current_aperture.write(current_valve);
        }
    }
}