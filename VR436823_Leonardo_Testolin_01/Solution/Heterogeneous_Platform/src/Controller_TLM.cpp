#include "Controller_TLM.hpp"

//costruttore e inizializzazione delle varibili
Controller::Controller(sc_module_name name,
                       sc_uint<32> key0,
                       sc_uint<32> key1,
                       sc_uint<32> key2,
                       sc_uint<32> key3,
                       sc_uint<32> delta): 
sc_module(name), target_socket("target"), key0(key0), key1(key1), key2(key2), key3(key3),delta(delta)
{
    initiator_socket(*this);
    target_socket(*this);
    m_qk.set_global_quantum(sc_time(5, SC_MS));
    m_qk.reset();
    thrsh = 0.7;
}

//funzione primitiva b_transport
void Controller::b_transport(tlm::tlm_generic_payload &trans, sc_time &t)
{
    // timing=SC_ZERO_TIME;
    water_level = (*((waterTank *)trans.get_data_ptr())).waterLevel; //imposto il segnale water_level con il valore della struttura
    trans.set_response_status(tlm::TLM_OK_RESPONSE);
    run(); //chiamo run
}

//funzione xtea
void Controller::xtea_cyp(int command)
{
    sc_uint<64> sum = 0;
    sc_uint<32> v0, v1, temp;
    sc_uint<6> i;
    v0 = command/2;
    v1 = command%2;
    for (i = 0; i < 32; i++)
    {
        if ((sum & 3) == 0)
            temp = key0;
        else if ((sum & 3) == 1)
            temp = key1;
        else if ((sum & 3) == 2)
            temp = key2;
        else
            temp = key3;
        v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + temp);
        sum += delta;
        if (((sum >> 11) & 3) == 0)
            temp = key0;
        else if (((sum >> 11) & 3) == 1)
            temp = key1;
        else if (((sum >> 11) & 3) == 2)
            temp = key2;
        else
            temp = key3;
        v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + temp);
    }
    word0 = v0;
    word1 = v1;
}

//funzione run che carica i dati nel payload
void Controller::run()
{
    valvola_s packet; //valvola
    tlm::tlm_generic_payload payload; //creo il payload
    sc_time local_time = m_qk.get_local_time();
    payload.set_data_ptr((unsigned char *)&packet); //puntatore alla struttura
    payload.set_write(); //modalità scrittura
    local_time = m_qk.get_local_time();
    //assegno le chiavi
    packet.key0=key0;
    packet.key1=key1;
    packet.key2=key2;
    packet.key3=key3;
    //in base al livello dell'acqua vado a creare il comando criptato e assegno le parole criptate
    // alla struttura e imposto la thresh
    if (water_level > 8.8)
    {
        thrsh *= 0.7;
        xtea_cyp(CLOSE);
        packet.word0 = word0;
        packet.word1 = word1;
    }
    else if (water_level < 5)
    {
        thrsh *= 1.1;
        xtea_cyp(OPEN);
        packet.word0 = word0;
        packet.word1=word1;
    }
    else{
        xtea_cyp(IDLE);
        packet.word0 = word0;
        packet.word1=word1;
    }

    packet.tresholding = thrsh; //assegno la thresh dentor la struttura
    initiator_socket->b_transport(payload, local_time); //chiamo la b_transport
}
//metodi non usati
void Controller::invalidate_direct_mem_ptr(
    uint64 start_range,
    uint64 end_range)
{
}

tlm::tlm_sync_enum Controller::nb_transport_bw(tlm::tlm_generic_payload &trans,
                                               tlm::tlm_phase &phase,
                                               sc_time &t)
{
    return tlm::TLM_COMPLETED;
}

tlm::tlm_sync_enum Controller::nb_transport_fw(tlm::tlm_generic_payload &trans,
                                               tlm::tlm_phase &phase,
                                               sc_time &t)
{
    return tlm::TLM_COMPLETED;
}

unsigned int Controller::transport_dbg(tlm::tlm_generic_payload &trans)
{
    return 0;
}

bool Controller::get_direct_mem_ptr(tlm::tlm_generic_payload &trans, tlm::tlm_dmi &dmi_data)
{
    return 0;
}
