#include "root_LT.hh"
#include "root_LT_testbench.hh"

class root_top : public sc_module
{

private:

  root_LT  m_target;

  root_LT_testbench m_initiator;


public:

  root_top(sc_module_name name)
    : sc_module(name)
    , m_target("target")
    , m_initiator("initiator")
  {
    // bind TLM ports
    m_initiator.initiator_socket(m_target.target_socket);
  }

};

int main(int argc, char* argv[])
{

  root_top top("top");
  sc_start();

  return 0;

}
