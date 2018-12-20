#include "dist_LT.hh"
#include "dist_LT_testbench.hh"

class dist_top : public sc_module
{

private:

  dist_LT  m_target;

  dist_LT_testbench m_initiator;


public:

  dist_top(sc_module_name name)
    : sc_module(name)
    , m_target("target")
    , m_initiator("initiator")
  {
    m_initiator.initiator_socket(m_target.target_socket);
  }

};

int main(int argc, char* argv[])
{

  dist_top top("top");

  sc_start();

  return 0;

}
