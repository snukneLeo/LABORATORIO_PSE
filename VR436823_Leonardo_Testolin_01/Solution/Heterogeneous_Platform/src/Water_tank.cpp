#include "Water_tank.hpp"

//costruttore
Water_tank::Water_tank( sc_core::sc_module_name ):
    in("in"), out("out"), gainA("gainA",0.6), gainK2("gainK2",0.03),
    subTwoSignal("subTwoSignal"), integratore("integratore"),
    convertion("convertion"), sig1("sig1"),sig2("sig2"),sig3("sig3"),
    sig4("sig4"),sig5("sig5"),convertionLSFtoTDF("convertionLSFtoTDF")
{
   //ingresso
   convertion.inp(in);
   convertion.y(sig1);
   //costante moltiplicativa a
   gainA.x(sig1);
   gainA.y(sig2);
   // sottrazione derivante dal moltiplicatore
   subTwoSignal.x1(sig2);
   subTwoSignal.x2(sig5);
   subTwoSignal.y(sig3);
   //ingresso integratore dal moltiplicatore
   integratore.x(sig3);
   integratore.y(sig4); //output
   //ingresso per la costante k2
   gainK2.x(sig4);
   gainK2.y(sig5);
   //convertion from from lsf to tdf
   convertionLSFtoTDF.x(sig4);
   convertionLSFtoTDF.outp(out);
}