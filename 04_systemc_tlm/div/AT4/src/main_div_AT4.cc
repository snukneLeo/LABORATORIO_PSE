#include "div_AT4.hh"
#include "div_AT4_testbench.hh"

class div_top : public sc_module
{

private:

  div_AT4  m_target;

  div_AT4_testbench m_initiator;


public:

  div_top(sc_module_name name)
    : sc_module(name)
    , m_target("target")
    , m_initiator("initiator")
  {
    m_initiator.initiator_socket(m_target.target_socket);
  }

};

int main(int argc, char* argv[])
{

  div_top top("top");

  sc_start();

  return 0;

}
