#include "root_RTL.hh"

void root_RTL :: datapath(void){
  cout<<sc_simulation_time()<<" - "<<name()<<" - DATAPATH"<<endl;
  if (rst.read() == 0){
	STATUS = Reset_ST;
  }
  else if (clk.read() == 1) 
	{
	STATUS = NEXT_STATUS;
	
	switch(STATUS){
	case Reset_ST:
		dout.write(0);
		dout_rdy.write(0);
		break;
	case ST_0:
		dout.write(0);
		dout_rdy.write(0);
		Rem.write(0);
		Root.write(0);
		Counter.write(0);
		break;
	case ST_1:
		Number = din.read();
		if (din.read()>0){
			cout<<"Number = "<<din.read()<<endl;
		}
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
		cout<<"Result = "<<(Root.read() >> 1)<<endl;
		dout.write(Root.read() >> 1);
		dout_rdy.write(1);
		break;
	} // end switch
  }
}


void root_RTL :: fsm(void){
  cout<<sc_simulation_time()<<" - "<<name()<<" - FSM"<<endl;
  NEXT_STATUS = STATUS;

  switch(STATUS){
  case Reset_ST:
    NEXT_STATUS = ST_0;
    break;

  case ST_0:
    if (din_rdy.read() == 1){
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
