#include "root_RTL.hh"

void root_RTL :: datapath(void){
    if (rst.read() == 0){
        STATUS = Reset_ST;
    }
    else if (clk.read() == 1) {


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
                dout.write(Root.read() >> 1);
                dout_rdy.write(1);
                break;
        } // end switch
    }
}


void root_RTL :: fsm(void){

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




// CHECKERS

void root_RTL :: property1(void){
    // if din_rdy == 1 then dout_rdy == 1 
    // in less than 100 clock cycles

    int count = 0;
    bool true_property = false;

    while(true){
        if (din_rdy.read() == 1){
            while((count < 100)&(!true_property)){
                wait();
                if (dout_rdy.read() == 1)
                    true_property = true;
            }

            if (true_property)
                cout <<
                    "\033[34m" <<
                    "[CHECK: ] property 1 is true" << "\033[0m" << endl;
            else {
                cout <<
                    "\033[34m" << 
                    "[CHECK: ] property 1 is false"
                    << "\033[0m" << endl;
            }
            count = 0;
            true_property = false;
        }
        wait();
    }
}

void root_RTL :: property2(void){
    // if din_rdy == 0 then dout == 0 and dout_rdy == 0

    while(true){
        if (din_rdy.read() == 0){
            if ((dout.read() == 0)&&(dout_rdy.read() == 0))
                cout << 
                    "\033[35m" << 
                    "[CHECK: ] property 2 is true" << 
                    "\033[0m" << endl;
            else{
                cout <<
                    "\033[35m" <<
                    "[CHECK: ] property 2 is false" << "\033[0m" << endl;
            }
        }
        wait();
    }
}

void root_RTL :: property4(void){
    // if Counter < 16 then STATUS = ST4

    while(true){
        if (Counter.read() < 16){
            if (STATUS.read() == ST_4)       
                cout <<
                    "\033[32m" <<
                    "[CHECK: ] property 4 is true" << "\033[0m" << endl;
            else{
                cout << 
                    "\033[32m" << 
                    "[CHECK: ] property 4 is false" << "\033[0m" << endl;
            }
        }
        wait();
    }
}



