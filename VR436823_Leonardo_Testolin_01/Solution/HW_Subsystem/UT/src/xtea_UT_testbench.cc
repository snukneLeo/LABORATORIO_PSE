#include "xtea_UT_testbench.hh"


// costuttore -> inizializzo il socket initiator
xtea_UT_testbench::xtea_UT_testbench(sc_module_name name)
  : sc_module(name)
{

  initiator_socket(*this);
  //chiamo la thread
  SC_THREAD(run);

}

//metodo run per la creazione e l'avvio della simulazione
void xtea_UT_testbench::run()
{
  sc_time local_time;
  iostruct xtea_packet; //instanza della srtuttura
  tlm::tlm_generic_payload payload;	 //creazione del payload
  
  payload.set_data_ptr((unsigned char*) &xtea_packet); //puntatore alla strutura
  payload.set_address(0); // imposto zero -> chiamata tra iniator e target (forward solamente)
  payload.set_write(); // payload in scrittura

  ///////////////////////////////////////////////////////////////////////////////////////////////////////
  //inserisco i dati nella srtuttura
  xtea_packet.mode = 0;
  xtea_packet.word0 = 0x12345678; 
  xtea_packet.word1 = 0x9abcdeff; 
  xtea_packet.key0 = 0x6a1d78c8; 
  xtea_packet.key1 = 0x8c86d67f; 
  xtea_packet.key2 = 0x2a65bfbe; 
  xtea_packet.key3 = 0xb4bd6e46;

  cout << "Original text: " << hex << xtea_packet.word0 << "," << hex << xtea_packet.word1 << "\n";

  //Chiamata da initaor a target
  initiator_socket->b_transport(payload, local_time);
  cout << "[TB:] Chiamata da initiator a target. MODE: write" << "\n";
  //stampo i risultati ottenuti
  if (payload.get_response_status() == tlm::TLM_OK_RESPONSE) 
  {
    cout << "Encrypted text: " << hex << xtea_packet.result0 << "," << hex << xtea_packet.result1 << "\n";
  }

  //imposto la modalità
  xtea_packet.mode = 1;

  //Chiamata da initaor a target
  initiator_socket->b_transport(payload, local_time);
  cout << "[TB:] Chiamata da initiator a target. MODE: read" << "\n";
  payload.set_read(); //payload in lettura
    //stampo i risultati ottenuti
  if (payload.get_response_status() == tlm::TLM_OK_RESPONSE) 
  {
    cout << "Decrypted text: " << hex << xtea_packet.result0 << "," << hex << xtea_packet.result1 << "\n";
  }

  sc_stop(); 
}

void xtea_UT_testbench::invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range)
{
  
}

tlm::tlm_sync_enum xtea_UT_testbench::nb_transport_bw(tlm::tlm_generic_payload &  trans, tlm::tlm_phase &  phase, sc_time &  t)
{
  return tlm::TLM_COMPLETED;
}
