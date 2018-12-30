#include "RTL-TLM_transactor.hpp"
//costruttore inizializzo la socket e la thread con il metodo run
Transactor_RTL_TLM::Transactor_RTL_TLM(sc_module_name name) : sc_module(name)

{
    initiator_socket(*this);
    m_qk.set_global_quantum(sc_time(100, SC_NS));
    m_qk.reset();

    SC_THREAD(run);
}

//metodo run che chiama la traduzione ogni 5 secondi
void Transactor_RTL_TLM::run(){
    while(1)
    {
        wait(4,SC_SEC); //con attesa di 4 secondi la curva si stabilizza meglio causa i ritardi
        transduce(); //chiamata del trnsattore
    }
}

void Transactor_RTL_TLM::transduce()
{
    waterTank packet; //struttura
    tlm::tlm_generic_payload payload; //creazione del payload
    sc_time local_time = m_qk.get_local_time();
    payload.set_data_ptr((unsigned char *)&packet); //puntatore alla struttura

    payload.set_write(); //chiamata in scrittura

    packet.waterLevel = water_level_rt.read(); //salvo dentor la struttura il livello dell'acqua
    initiator_socket->b_transport(payload, local_time); //chiamo la b_transport
}

void Transactor_RTL_TLM::invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range)
{}
tlm::tlm_sync_enum Transactor_RTL_TLM::nb_transport_bw(tlm::tlm_generic_payload &  trans, tlm::tlm_phase &  phase, sc_time &  t)
{
    return tlm::TLM_ACCEPTED;
}
