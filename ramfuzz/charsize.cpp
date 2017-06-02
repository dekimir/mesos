#include <iostream>
#include <string>

#include "fuzz.hpp"

using namespace std;
using namespace ramfuzz::runtime;

int main(int argc, char* argv[])
{
  gen g(argc, argv);
  const auto size = g.between<size_t>(0, 999999999);
  mesos::TaskID t;
  t.set_value(new char[1000], /*stoi(argv[1])*/ size);
}
