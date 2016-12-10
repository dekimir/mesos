#include "fuzz.hpp"

namespace ramfuzz {

// Descriptor
rfgoogle_protobuf_Descriptor::control
rfgoogle_protobuf_Descriptor::control::make(runtime::gen&)
{
}

template <>
void runtime::gen::set_any<google::protobuf::Descriptor>(
  google::protobuf::Descriptor&)
{
}

template <>
void runtime::gen::set_any<google::protobuf::Descriptor>(
  google::protobuf::Descriptor*&)
{
}

template <>
void runtime::gen::set_any<google::protobuf::Descriptor>(
  const google::protobuf::Descriptor*&)
{
}

// FieldDescriptor
rfgoogle_protobuf_FieldDescriptor::control
rfgoogle_protobuf_FieldDescriptor::control::make(runtime::gen&)
{
}

template <>
void runtime::gen::set_any<google::protobuf::FieldDescriptor>(
  google::protobuf::FieldDescriptor&)
{
}

template <>
void runtime::gen::set_any<google::protobuf::FieldDescriptor>(
  google::protobuf::FieldDescriptor*&)
{
}

template <>
void runtime::gen::set_any<google::protobuf::FieldDescriptor>(
  const google::protobuf::FieldDescriptor*&)
{
}

// OneofDescriptor
rfgoogle_protobuf_OneofDescriptor::control
rfgoogle_protobuf_OneofDescriptor::control::make(runtime::gen&)
{
}

template <>
void runtime::gen::set_any<google::protobuf::OneofDescriptor>(
  google::protobuf::OneofDescriptor&)
{
}

template <>
void runtime::gen::set_any<google::protobuf::OneofDescriptor>(
  google::protobuf::OneofDescriptor*&)
{
}

template <>
void runtime::gen::set_any<google::protobuf::OneofDescriptor>(
  const google::protobuf::OneofDescriptor*&)
{
}

// EnumValueDescriptor
rfgoogle_protobuf_EnumValueDescriptor::control
rfgoogle_protobuf_EnumValueDescriptor::control::make(runtime::gen&)
{
}

template <>
void runtime::gen::set_any<google::protobuf::EnumDescriptor>(
  google::protobuf::EnumDescriptor&)
{
}

template <>
void runtime::gen::set_any<google::protobuf::EnumDescriptor>(
  google::protobuf::EnumDescriptor*&)
{
}

template <>
void runtime::gen::set_any<google::protobuf::EnumDescriptor>(
  const google::protobuf::EnumDescriptor*&)
{
}

unsigned runtime::spinlimit = 10;

} // namespace ramfuzz

using namespace ramfuzz;
using namespace ramfuzz::runtime;

int main(int argc, char* argv[])
{
  gen g(argc, argv);
  auto c = spin_roulette<rfmesos_MesosSchedulerDriver::control>(g);
  return bool(c);
}
