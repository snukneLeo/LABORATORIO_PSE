#include "root_RTL.hh"

void root_RTL :: elaborate_SQRT_FSM(void){
  if (reset.read() == 0){
    STATUS = Reset_ST;
  }
  else if (clk.read() == 1) {


    STATUS = NEXT_STATUS;

    switch(STATUS){
      case Reset_ST:
        result_port.write(0);
        result_isready.write(0);
        break;
      case ST_0:
        result_port.write(0);
        result_isready.write(0);
        Rem.write(0);
        Root.write(0);
        Counter.write(0);
        break;
      case ST_1:
        Number = number_port.read();
        break;
      case ST_2:
        if (Counter.read() < 16){
          Rem.write((Rem.read() << 2) + (Number.read() >> 30));
          Number.write(Number.read() << 2);
          Root.write(Root.read() << 1);
        }
        break;
      case ST_3:
        if (Root.read() < Rem.read()){
          Rem.write(Rem.read() - Root.read() - 1);
          Root.write(Root.read() + 2);
        }
        Counter.write(Counter.read() + 1);
        break;
      case ST_4:
        result_isready.write(1);
        result_port.write( Root.read() >> 1 );
        break;
    } 
  }
}


void root_RTL :: elaborate_SQRT(void){


  NEXT_STATUS = STATUS;

  switch(STATUS){
    case Reset_ST:
      NEXT_STATUS = ST_0;
      break;

    case ST_0:
      if (number_isready.read() == 1){
        NEXT_STATUS = ST_1;
      } else {
        NEXT_STATUS = ST_0;
      }
      break;

    case ST_1:
      NEXT_STATUS = ST_2;
      break;

    case ST_2:
      if (Counter.read() < 16){
        NEXT_STATUS = ST_3;
      } else {
        NEXT_STATUS = ST_4;
      }
      break;

    case ST_3:
      NEXT_STATUS = ST_2;
      break;

    case ST_4:
      NEXT_STATUS = ST_0;
      break;
  }
}
