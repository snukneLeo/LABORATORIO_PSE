#include "dist_UT.hh"
#include "dist_UT_testbench.hh"

class dist_top : public sc_module
{

private:

  dist_UT  m_target;

  dist_UT_testbench m_initiator;


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
