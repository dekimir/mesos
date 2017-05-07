#include "fuzz.hpp"

using namespace ramfuzz::runtime;

int main(int argc, char* argv[])
{
  gen g(argc, argv);
  ramfuzz::harness<mesos::TaskID> h(g);
  h.CopyFrom0();
}
