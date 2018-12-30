#include "xtea_LT.hh"
#include "xtea_LT_testbench.hh"

class xtea_top : public sc_module
{

private:

  xtea_LT  m_target;

  xtea_LT_testbench m_initiator;


public:

  xtea_top(sc_module_name name)
    : sc_module(name)
    , m_target("target")
    , m_initiator("initiator")
  {
    // collegamento tra initiator e target
    m_initiator.initiator_socket(m_target.target_socket);
  }

};

int main(int argc, char* argv[])
{

  xtea_top top("top");
  sc_start();

  return 0;

}
