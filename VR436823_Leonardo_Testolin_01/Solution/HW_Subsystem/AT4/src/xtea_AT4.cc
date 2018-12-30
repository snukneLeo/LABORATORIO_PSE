#include "xtea_AT4.hh"

// cosrtuttore 
// inizializzazione del socket e del IOPROCESS thread
xtea_AT4::xtea_AT4(sc_module_name name_)
: sc_module(name_)
, target_socket("target_socket")
, pending_transaction(NULL)
{
  
  target_socket(*this);
  SC_THREAD(IOPROCESS);
  
}

// nb_blocking che permete di chiamare l'initiator
//initiator a target
tlm::tlm_sync_enum xtea_AT4::nb_transport_fw(tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_time& t)
{
  //check se il tutto funziona e se è corretto
  if (pending_transaction != NULL) 
  {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
    return tlm::TLM_COMPLETED;
  }

  //la prima fase è di begin request per l'inizio della transazione
  if (phase != tlm::BEGIN_REQ) 
  {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
    return tlm::TLM_COMPLETED;
  }

  cout<<"\t\t[XTEA:] Invocazione della nb_transport_fw (initiator - target)"<<endl;
  cout<<"\t\t[xtea:] Attivazione della funzione IOPROCESS"<<endl;
  pending_transaction = &trans; // scarico il payload 
  ioDataStruct = *((iostruct*) trans.get_data_ptr()); // aggiorno i dati della struttura

  phase = tlm::END_REQ; // fase di end request quindi passa la computazione al target

  // attivazione con notify (risveglio) del metodo IOPROCESS
  io_event.notify();
  
  // ritorno il controllo all'initiator
  cout<<"\t\t[XTEA:] Fine della nb_transport_fw primitive"<<endl;
  return tlm::TLM_UPDATED;
  
}

//funzione IOPROCESS
void xtea_AT4::IOPROCESS()
{

  sc_time timing_annotation;

  while (true) 
  {
    //sbloccato non appena c'è la fase di end request
    wait(io_event);
    //se sono qui c'è stata l'attivazione da parte dell'initiator
    cout<<"\t\t[XTEA:] IOPROCESS è stato avviato"<<endl;
    
    //aspetto un certo tempi di ritardo

    wait(100, SC_NS);    

    //stessa metodologia per il write e read da parte della transazione per chiamare
    //la funzione xtea in cript e decript
    if (pending_transaction->is_write())  //cript
    {
      //chiamata a funzione
      xtea_AT4_function();
      //salvo i dati nella srtuttura
      ioDataStruct.result0 = tmp_result0;
      ioDataStruct.result1 = tmp_result1;
      //aggiorno la struttura
      pending_transaction->set_response_status(tlm::TLM_OK_RESPONSE);
      *((iostruct*) pending_transaction->get_data_ptr()) = ioDataStruct;

    }
    else //decript
    {
      //stessa cosa per la decript come cript
      xtea_AT4_function();
      ioDataStruct.result0 = tmp_result0;
      ioDataStruct.result1 = tmp_result1;
      pending_transaction->set_response_status(tlm::TLM_OK_RESPONSE);
      *((iostruct*) pending_transaction->get_data_ptr()) = ioDataStruct;
    }
    
    //inizio la fase si begin Reposnde
    
    tlm::tlm_phase phase = tlm::BEGIN_RESP;
    
    cout<<"[TB:] Invcoca la nb_transport_bw - modalità: write"<<endl;
    //inizio la chiamata
    target_socket->nb_transport_bw(*pending_transaction, phase, timing_annotation);
    pending_transaction = NULL;

  }

}

//funzione che implemnta lo xtea
void xtea_AT4::xtea_AT4_function() 
{
  sc_uint<64> sum;
  sc_uint<32> i, delta, v0, v1, temp;
  sum = 0;
  tmp_result0 = 0;
  tmp_result1 = 0;

  if (ioDataStruct.mode == 0)  //cript
  {
    v0 = ioDataStruct.word0;
    v1 = ioDataStruct.word1;
    delta = 0x9e3779b9;
    for (i = 0; i < 32; i++) 
    {

      if ((sum & 3) == 0)
        temp = ioDataStruct.key0;
      else if ((sum & 3) == 1)
        temp = ioDataStruct.key1;
      else if ((sum & 3) == 2)
        temp = ioDataStruct.key2;
      else
        temp = ioDataStruct.key3;

      v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + temp);

      sum += delta;

      if (((sum >> 11) & 3) == 0)
        temp = ioDataStruct.key0;
      else if (((sum >> 11) & 3) == 1)
        temp = ioDataStruct.key1;
      else if (((sum >> 11) & 3) == 2)
        temp = ioDataStruct.key2;
      else
        temp = ioDataStruct.key3;

      v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + temp);
    }
  }
  else if (ioDataStruct.mode == 1)  //decript
  {
    delta = 0x9e3779b9;
    sum = delta * 32;
    v0 = ioDataStruct.result0;
    v1 = ioDataStruct.result1;
    for (i = 0; i < 32; i++) 
    {
      if (((sum >> 11) & 3) == 0)
        temp = ioDataStruct.key0;
      else if (((sum >> 11) & 3) == 1)
        temp = ioDataStruct.key1;
      else if (((sum >> 11) & 3) == 2)
        temp = ioDataStruct.key2;
      else
        temp = ioDataStruct.key3;

      v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + temp);

      sum -= delta;

      if ((sum & 3) == 0)
        temp = ioDataStruct.key0;
      else if ((sum & 3) == 1)
        temp = ioDataStruct.key1;
      else if ((sum & 3) == 2)
        temp = ioDataStruct.key2;
      else
        temp = ioDataStruct.key3;

      v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + temp);
    }
  }
  tmp_result0 = v0;
  tmp_result1 = v1;
}

//meotdi non necessari
void xtea_AT4::b_transport(tlm::tlm_generic_payload& trans, sc_time& t)
{
  
}

bool xtea_AT4::get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmi_data)
{
  return false;
}

unsigned int xtea_AT4::transport_dbg(tlm::tlm_generic_payload& trans)
{
  return 0;
}
