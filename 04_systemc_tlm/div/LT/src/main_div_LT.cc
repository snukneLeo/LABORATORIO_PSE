#include "div_LT.hh"
#include "div_LT_testbench.hh"

class div_top : public sc_module
{

private:

  div_LT  m_target;

  div_LT_testbench m_initiator;


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
