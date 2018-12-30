#include "XTEA_RTL_testbench.hh"
#include <fstream>
#include <sstream>
#include <string>

XTEA_RTL_testbench::XTEA_RTL_testbench(sc_module_name name) : sc_module(name) 
{
  //definiizone della thread con metodo run
  //thread sensibile come definito in SC_MODULE al clock e al reset
  SC_THREAD(run);
  sensitive << clk.pos() << rst.pos();
}
//definizione del metodo run e quindi dell'effettiva stimolazione dei segnali del sistema
void XTEA_RTL_testbench::run() 
{
  sc_uint<32> text[2] = {0x12345678, 0x9abcdeff};
  sc_uint<32> key[4] = {0x6a1d78c8, 0x8c86d67f, 0x2a65bfbe, 0xb4bd6e46};

  /// Modalità encrypt
  mode.write(0);

  cout << "Original text: " << hex << text[0] << "," << hex << text[1] << "\n";

  //inserimento chiavi
  key_i0.write(key[0]);
  key_i1.write(key[1]);
  key_i2.write(key[2]);
  key_i3.write(key[3]);
  word0.write(text[0]);
  word1.write(text[1]);
  input_ready.write(true);
  wait(100); //attesa per la propagazione dei segnali

  //ritorno delle parole criptate
  text[0] = out0.read();
  text[1] = out1.read();
  input_ready.write(false);
  wait(); //attesa per la propagazione dei segnali

  cout << "Encrypted text: " << hex << text[0] << "," << hex << text[1] << "\n";

  /// Decrypt mode
  mode.write(true);
  wait(); //attesa per la propagazione dei segnali

  //inserimento chiavi
  key_i0.write(key[0]);
  key_i1.write(key[1]);
  key_i2.write(key[2]);
  key_i3.write(key[3]);
  word0.write(text[0]);
  word1.write(text[1]);
  input_ready.write(true);
  wait(150); //attesa per la propagazione dei segnali

  //ritorno delle parole decriptate
  text[0] = out0.read();
  text[1] = out1.read();
  input_ready.write(false);

  cout << "Decrypted text: " << hex << text[0] << "," << hex << text[1] << "\n";

  // Simulazione terminata
  sc_stop();
}