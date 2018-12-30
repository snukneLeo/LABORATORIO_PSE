#include "XTEA_RTL.hh"
#include "XTEA_RTL_testbench.hh"

int sc_main(int argc, char **argv) 
{
  //definizione dei segnali necessari per il collegamento dei differenti moduli
  //xtea e testbench
  sc_clock clk; 
  sc_signal<bool> rst, input_ready;
  sc_signal<sc_uint<1> > mode;

  sc_signal<sc_uint<32> > word0;
  sc_signal<sc_uint<32> > word1;
  sc_signal<sc_uint<32> > key_i0;
  sc_signal<sc_uint<32> > key_i1;
  sc_signal<sc_uint<32> > key_i2;
  sc_signal<sc_uint<32> > key_i3;
  sc_signal<sc_uint<32> > out0;
  sc_signal<sc_uint<32> > out1;
  sc_signal<bool> dout;

  XTEA_RTL xtea("xtea_rtl");
  XTEA_RTL_testbench test("xtea_rtl_testbench");

  // creazione del file per la traccia del sistema
  sc_trace_file *fp = sc_create_vcd_trace_file("wave");
  sc_trace(fp, clk, "clk");
  sc_trace(fp, rst, "rst");
  sc_trace(fp, input_ready, "input_ready");
  sc_trace(fp, mode, "mode");
  sc_trace(fp, word0, "text_input(0)");
  sc_trace(fp, word1, "text_input(1)");
  sc_trace(fp, key_i0, "key_input(0)");
  sc_trace(fp, key_i1, "key_input(1)");
  sc_trace(fp, key_i2, "key_input(2)");
  sc_trace(fp, key_i3, "key_input(3)");
  sc_trace(fp, out0, "data_output(0)");
  sc_trace(fp, out1, "data_output(1)");

  //collegamento dei segnali xtea con i segnali definiti qui sopra
  xtea.clk(clk);
  xtea.word0(word0);
  xtea.word1(word1);
  xtea.key1(key_i0);
  xtea.key2(key_i1);
  xtea.key3(key_i2);
  xtea.key4(key_i3);
  xtea.mode(mode);
  xtea.din_rdy(input_ready);
  xtea.reset(rst);
  xtea.out0(out0);
  xtea.out1(out1);
  xtea.dout_rdy(dout);

  //collegamento dei segnali testbench con i segnali definiti qui sopra
  test.clk(clk);
  test.rst(rst);
  test.word0(word0);
  test.word1(word1);
  test.key_i0(key_i0);
  test.key_i1(key_i1);
  test.key_i2(key_i2);
  test.key_i3(key_i3);
  test.out0(out0);
  test.out1(out1);
  test.input_ready(input_ready);
  test.mode(mode);
  test.dout_rdy(dout);


  sc_start();

  //sc_close_vcd_trace_file(fp);

  return 0;
}