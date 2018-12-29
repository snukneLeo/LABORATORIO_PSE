#include "Xtea_RTL.hpp"

void XTEA_RTL::fsm() {
  NEXT_STATUS = STATUS;
  switch (STATUS) {
  case IDLE:
    if (input_ready.read()) {
      NEXT_STATUS = BUSY;
    } else
      NEXT_STATUS = IDLE;
    break;
  case BUSY:
    if (input_ready.read())
      NEXT_STATUS = BUSY;
    else
      NEXT_STATUS = IDLE;
    break;
  }
}

void XTEA_RTL::datapath() {
  if (rst.read()) {
    STATUS = IDLE;
  } else {
    STATUS = NEXT_STATUS;
    sc_uint<32> tmp[2];

    switch (STATUS) {
    case IDLE:break;
    case BUSY:
      key0.write(key_i0.read());
      key1.write(key_i1.read());
      key2.write(key_i2.read());
      key3.write(key_i3.read());
      word0_pr.write(word0.read());
      word1_pr.write(word1.read());
      xtea(word0_pr, word1_pr, key0, key1, key2, key3, mode, &tmp[0],
           &tmp[1]);
      out0.write(tmp[0]);
      out1.write(tmp[1]);
      break;
    }
  }
}

void XTEA_RTL::xtea(sc_uint<32> word0, sc_uint<32> word1, sc_uint<32> key0,
                    sc_uint<32> key1, sc_uint<32> key2, sc_uint<32> key3,
                    sc_uint<1> mode, sc_uint<32> *result0, sc_uint<32> *result1) {
  sc_uint<64> sum;
  sc_uint<32> i, delta, v0, v1, temp;
  v0 = word0;
  v1 = word1;
  sum = 0;
  *result0 = 0;
  *result1 = 0;

  if (mode == 0) {
    // encipher
    delta = 0x9e3779b9;
    for (i = 0; i < 32; i++) {

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
  } else if (mode == 1) {
    // decipher
    delta = 0x9e3779b9;
    sum = delta * 32;
    for (i = 0; i < 32; i++) {

      if (((sum >> 11) & 3) == 0)
        temp = key0;
      else if (((sum >> 11) & 3) == 1)
        temp = key1;
      else if (((sum >> 11) & 3) == 2)
        temp = key2;
      else
        temp = key3;

      v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + temp);

      sum -= delta;

      if ((sum & 3) == 0)
        temp = key0;
      else if ((sum & 3) == 1)
        temp = key1;
      else if ((sum & 3) == 2)
        temp = key2;
      else
        temp = key3;

      v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + temp);
    }
  }
  *result0 = v0;
  *result1 = v1;
}
