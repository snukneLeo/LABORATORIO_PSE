#include "PlantTransactor.hh"

PlantTransactor::PlantTransactor( sc_module_name name ) :
  sc_module( name ),
  target_socket( "target_socket" ),
  pending_transaction( NULL )
{
  target_socket( *this );

#ifdef TRACING
  SC_THREAD( _trace );
  log = fopen("logs/execution.log", "w");
#endif
}

void PlantTransactor::b_transport( 
    tlm::tlm_generic_payload& trans,
    sc_time & t )
{
  //implementation of the b_transport
  ioDataStruct = *((iostruct*) trans.get_data_ptr());
  transduce();
  trans.set_data_ptr((unsigned char*) &ioDataStruct);

}

bool PlantTransactor::get_direct_mem_ptr(
    tlm::tlm_generic_payload& trans, 
    tlm::tlm_dmi& dmi_data)
{
  return false;
}

tlm::tlm_sync_enum PlantTransactor::nb_transport_fw(
    tlm::tlm_generic_payload& trans, 
    tlm::tlm_phase& phase, 
    sc_time& t)
{
  return tlm::TLM_COMPLETED;
}

unsigned int PlantTransactor::transport_dbg(
    tlm::tlm_generic_payload& trans)
{
  return 0;
}

void PlantTransactor::transduce()
{
  //write to ports and viceversa...
  value_bw.write( ioDataStruct.value_bw );
  ioDataStruct.value_fw = value_fw.read();
}

void PlantTransactor::end_of_elaboration()
{

}

void PlantTransactor::reset()
{
}

PlantTransactor::~PlantTransactor()
{
#ifdef TRACING
  if( log != NULL ) fclose(log);
#endif
}

#ifdef TRACING
void PlantTransactor::_trace()
{
  while(true)
  {
    wait(20, sc_core::SC_MS);
    fprintf( log, "%f %f\n", sc_time_stamp().to_seconds(), value_fw.read() );
  }
}
#endif

