#include "fuzz.hpp"

using namespace google::protobuf;
using namespace ramfuzz::runtime;

namespace {

const Descriptor* makeDesc(gen& g)
{
  FileDescriptorProto fp;
  fp.mutable_message_type()->AddAllocated(
    g.make<DescriptorProto>(g.or_subclass));
  return g.make<DescriptorPool>()->BuildFile(fp)->message_type(0);
}

const FieldDescriptor* makeField(gen& g)
{
  FileDescriptorProto fp;
  fp.mutable_message_type()->AddAllocated(
    g.make<DescriptorProto>(g.or_subclass));
  fp.mutable_message_type(0)->mutable_field()->AddAllocated(
    g.make<FieldDescriptorProto>(g.or_subclass));
  return g.make<DescriptorPool>()->BuildFile(fp)->message_type(0)->field(0);
}

const OneofDescriptor* makeOneof(gen& g)
{
  // Seems like OneofDescriptorProto only houses the name -- the fields are
  // inserted right into the parent proto by the parser.  But then how does
  // OneofDescriptor get its FieldDescriptors??  Heh, descriptor.cc:4522
  // comments "We need to fill these in later". :) Hm, CrossLinkMessage() seems
  // to access a field's containing_oneof() -- where is that set?  I guess
  // FieldDescriptors are made with the appropriate OneofDescriptor* already set
  // (likely from the FieldDescriptorProto::oneof_index, set by the parser).
  FileDescriptorProto fp;
  fp.mutable_message_type()->AddAllocated(
    g.make<DescriptorProto>(g.or_subclass));
  fp.mutable_message_type(0)->mutable_field()->AddAllocated(
    g.make<FieldDescriptorProto>(g.or_subclass));
  fp.mutable_message_type(0)->mutable_field(0)->set_oneof_index(
    *g.make<int32_t>());
  fp.mutable_message_type(0)->mutable_oneof_decl()->AddAllocated(
    g.make<OneofDescriptorProto>());
  return g.make<DescriptorPool>()
    ->BuildFile(fp)
    ->message_type(0)
    ->field(0)
    ->containing_oneof();
}

const EnumValueDescriptor* makeEnumVal(gen& g)
{
  EnumDescriptorProto ep;
  ep.mutable_value()->AddAllocated(g.make<EnumValueDescriptorProto>());
  FileDescriptorProto fp;
  fp.mutable_enum_type()->AddAllocated(
    g.make<EnumDescriptorProto>(g.or_subclass));
  return g.make<DescriptorPool>()->BuildFile(fp)->enum_type(0)->value(0);
}

} // anonymous namespace

namespace ramfuzz {

harness<Descriptor>::harness(runtime::gen& g)
  : g(g), obj(*const_cast<Descriptor*>(makeDesc(g)))
{
}

harness<FieldDescriptor>::harness(runtime::gen& g)
  : g(g), obj(*const_cast<FieldDescriptor*>(makeField(g)))
{
}

harness<OneofDescriptor>::harness(runtime::gen& g)
  : g(g), obj(*const_cast<OneofDescriptor*>(makeOneof(g)))
{
}

harness<EnumValueDescriptor>::harness(runtime::gen& g)
  : g(g), obj(*const_cast<EnumValueDescriptor*>(makeEnumVal(g)))
{
}

unsigned runtime::spinlimit = 10;

} // namespace ramfuzz

int main(int argc, char* argv[])
{
  return gen(argc, argv).make<mesos::MesosSchedulerDriver>()->abort();
}
