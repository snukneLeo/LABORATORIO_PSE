#include "valve_AMS_TDF.hh"

valve::valve( sc_core::sc_module_name):
    command("command"), thresholding("thresholding"), current_aperture("current_aperture")
{
    current_valve = 0;
}

void valve::set_attributes()
{
}

//come collegare il segnale di ingresso alla valvola
//e come fare l'uscita della valvola
void valve::processing() //input: idle/open/close; thresholding
{
    //equazione integrante per l'apertura
    double delta = 0.25*get_timestep().to_seconds();
    if (command == IDLE) //a = 0
    {
        //scrittura dell'apertura invariata
        current_aperture.write(current_valve);
    }
    else if(command == OPEN) // a = 0.25
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
    else if(command == CLOSE) // a = -0.25
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