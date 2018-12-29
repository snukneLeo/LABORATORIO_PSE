#include "Controller_TLM.hpp"
#include "struct.hh"
#include "command_enum.hh"

TLM_controller::TLM_controller( sc_module_name name, 
                    sc_uint<32> key0,
                    sc_uint<32> key1,
                    sc_uint<32> key2,
                    sc_uint<32> key3,
                    sc_uint<32> delta):
sc_module(name), target_socket("target"),key0(key0), key1(key1), key2(key2), key3(key3),delta(delta)
{
  initiator_socket(*this);
  target_socket(*this);
  m_qk.set_global_quantum( sc_time( 20, SC_MS ));
  m_qk.reset();
  thresh = 0.7;
}

void TLM_controller::b_transport( tlm::tlm_generic_payload &trans, sc_time &t )
{
    waterLevel = (*((waterTank*) trans.get_data_ptr())).waterLevel;
    trans.set_response_status(tlm::TLM_OK_RESPONSE);
    run();
}

void TLM_controller::run()
{   
    //istanzio la struttura della valvola
    valve packet;
    tlm::tlm_generic_payload payload;
    sc_time local_time = m_qk.get_local_time();
    payload.set_data_ptr((unsigned char*) &packet);
    payload.set_write();
    local_time = m_qk.get_local_time();
    //setto le chiavi
    packet.key0 = key0;
    packet.key1 = key1;
    packet.key2 = key2;
    packet.key3 = key3;

    if(waterLevel >= 5 && waterLevel <= 8.8)
    {
        xtea_encrypt(IDLE);
        //parametri xtea
        packet.word0 = word0;
        packet.word1 = word1;
    }
    else if(waterLevel > 8.8)
    {
        thresh *= 0.7;
        xtea_encrypt(CLOSE);
        //parametri xtea
        packet.word0 = word0;
        packet.word1 = word1;
    }
    else if(waterLevel < 5)
    {
        thresh *= 1.1;
        xtea_encrypt(OPEN);
        //parametri xtea
        packet.word0 = word0;
        packet.word1 = word1; 
    }
    
    //parametro thresh
    packet.tresholding = thresh;
    initiator_socket->b_transport( payload, local_time );
}

void TLM_controller::xtea_encrypt(int command)
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

void TLM_controller::invalidate_direct_mem_ptr(uint64 start_range,uint64 end_range)
{

}

tlm::tlm_sync_enum TLM_controller::nb_transport_bw(tlm::tlm_generic_payload &trans,tlm::tlm_phase &phase,sc_time &t)
{
    return tlm::TLM_COMPLETED;
}

tlm::tlm_sync_enum TLM_controller::nb_transport_fw(tlm::tlm_generic_payload &trans,tlm::tlm_phase &phase,sc_time &t)
{
    return tlm::TLM_COMPLETED;
}

unsigned int TLM_controller::transport_dbg(tlm::tlm_generic_payload &trans)
{
    return 0;
}

bool TLM_controller::get_direct_mem_ptr(tlm::tlm_generic_payload &trans, tlm::tlm_dmi &dmi_data)
{
    return 0;
}

