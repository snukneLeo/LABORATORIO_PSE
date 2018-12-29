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
    double delta = 0.25*get_timestep().to_seconds();
    if (command == IDLE) //a = 0
    {
        current_aperture.write(current_valve);
    }
    else if(command == OPEN) // a = 0.25
    {
        if(current_valve > thresholding.read())
        {
            current_valve = thresholding.read();
            current_aperture.write(thresholding.read());
        }
        else
        {
            current_valve += delta;
            current_aperture.write(current_valve);
        } 
    }
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