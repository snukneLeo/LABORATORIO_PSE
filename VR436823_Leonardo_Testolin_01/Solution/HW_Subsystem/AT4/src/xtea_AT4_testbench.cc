#include "xtea_AT4_testbench.hh"

// costruttore 
// inizializza il socket e la thread
xtea_AT4_testbench::xtea_AT4_testbench(sc_module_name name)
  : sc_module(name)
  , response_pending(false)
{
  initiator_socket(*this);
  SC_THREAD(run);
}

// processo di initiator
void xtea_AT4_testbench::run()
{
  sc_time local_time = SC_ZERO_TIME;
  iostruct xtea_packet; //struttura
  tlm::tlm_generic_payload payload; //definico il payload	
  
  // setto la fase iniziale begin request
  tlm::tlm_phase phase = tlm::BEGIN_REQ;
  payload.set_address(0);
  payload.set_data_ptr((unsigned char*) &xtea_packet); //puntaore alla strutura da parte del payload
  payload.set_write(); //fase di scrittra

  ///////////////////////////////////
  //inserisco i dati
  xtea_packet.mode = 0;
  xtea_packet.word0 = 0x12345678; 
  xtea_packet.word1 = 0x9abcdeff; 
  xtea_packet.key0 = 0x6a1d78c8; 
  xtea_packet.key1 = 0x8c86d67f; 
  xtea_packet.key2 = 0x2a65bfbe; 
  xtea_packet.key3 = 0xb4bd6e46;
  ///////////////////////////////////
  cout << "Original text: " << hex << xtea_packet.word0 << "," << hex << xtea_packet.word1 << "\n";

  cout<<"[TB:] Invoca la nb_transport_fw - modalità: write"<<endl;
  tlm::tlm_sync_enum result = initiator_socket->nb_transport_fw(payload, phase, local_time); //invoco la primitiva

  if (result == tlm::TLM_COMPLETED)  //controllo che tutto sia corretto
  {
    //se il target fa subito la transazione qualcosa non va deve esssere notificato per andare avanti
    cout << "[ERROR:] Transaction error on nb_transport_fw. Forcing simulation stop." << endl;
    sc_stop();
  }

  //check sulla fase di chiusura
  if (phase != tlm::END_REQ) 
  {
    cout << "[ERROR: ] Unexpected protocol phase on nb_transport_fw. Forcing simulation stop." << endl;
    sc_stop();
  }

  cout<<"[TB:] Aspetto la nb_transport_bw che deve essere attivata "<<endl;
  response_pending = true; //richiesta in attesa
  wait(available_response); // aspettiamo che sia notificato

  cout << "Encrypted text: " << hex << xtea_packet.result0 << "," << hex << xtea_packet.result1 << "\n";
  
  //la richiesta di end request è finita 
  response_pending = false;
  phase = tlm::BEGIN_REQ;

  payload.set_address(0);
  payload.set_data_ptr((unsigned char*) &xtea_packet);
  payload.set_read();
  
  //modalità decript
  xtea_packet.mode = 1;

  cout<<"[TB:] Invoca la nb_transport_fw - modalità: read"<<endl;
  //invoco la nb_transport_fw
  result = initiator_socket->nb_transport_fw(payload, phase, local_time);

  ////controllo che tutto sia corretto
  if (result == tlm::TLM_COMPLETED) 
  {
    cout << "[ERROR:] Transaction error on nb_transport_fw. Forcing simulation stop." << endl;
    sc_stop();
  }

  if (phase != tlm::END_REQ) {
    cout << "[ERROR: ] Unexpected protocol phase on nb_transport_fw. Forcing simulation stop." << endl;
    sc_stop();
  }

  cout<<"[TB:] Waiting for nb_transport_bw to be invoked "<<endl;
  response_pending = true;
  wait(available_response);

  // if I am here, then the target has invoked the backward primitive and the AT4 protocol is finished
  // I can get the final result and print it
  response_pending = false;    

  if(payload.get_response_status() == tlm::TLM_OK_RESPONSE)
  {
    //se il target fa subito la transazione qualcosa non va deve esssere notificato per andare avanti
    cout << "Decrypted text: " << hex << xtea_packet.result0 << "," << hex << xtea_packet.result1 << "\n";
  }
  sc_stop();
}

//funzione primitiva nb_transport_bw
tlm::tlm_sync_enum xtea_AT4_testbench::nb_transport_bw(tlm::tlm_generic_payload &  trans, tlm::tlm_phase &  phase, sc_time &  t)
{
  
  //corretta begin request
  if (!response_pending) 
  {
    cout << "[ERROR:] Unexpected state for nb_transport_be" << endl;
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
    return tlm::TLM_COMPLETED;
  }
  
  //correta begin response
  if (phase != tlm::BEGIN_RESP) 
  {
    cout << "[ERROR:] Unexpected phase for nb_transport_be" << endl;
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
    return tlm::TLM_COMPLETED;
  }

  //attivazione
  available_response.notify();
  
  //fase finale di end response
  phase = tlm::END_RESP;
  return tlm::TLM_COMPLETED;
}


//metodi non necessari
void xtea_AT4_testbench::invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range)
{
  
}
