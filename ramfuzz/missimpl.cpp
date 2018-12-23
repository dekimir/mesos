/// @file Implements missing RamFuzz functions.

#include "fuzz.hpp"

using namespace google::protobuf;
using namespace ramfuzz::runtime;

namespace {

const Descriptor* makeDesc(gen& g)
{
  FileDescriptorProto fp;
  fp.mutable_message_type()->AddAllocated(
    g.make<DescriptorProto>(10, g.or_subclass));
  return g.make<DescriptorPool>(11)->BuildFile(fp)->message_type(0);
}

const FileDescriptor* makeFileDesc(gen& g)
{
  FileDescriptorProto fp;
  fp.mutable_message_type()->AddAllocated(
    g.make<DescriptorProto>(12, g.or_subclass));
  return g.make<DescriptorPool>(13)->BuildFile(fp);
}

const FieldDescriptor* makeField(gen& g)
{
  FileDescriptorProto fp;
  fp.mutable_message_type()->AddAllocated(
    g.make<DescriptorProto>(14, g.or_subclass));
  fp.mutable_message_type(0)->mutable_field()->AddAllocated(
    g.make<FieldDescriptorProto>(15, g.or_subclass));
  return g.make<DescriptorPool>(16)->BuildFile(fp)->message_type(0)->field(0);
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
    g.make<DescriptorProto>(17, g.or_subclass));
  fp.mutable_message_type(0)->mutable_field()->AddAllocated(
    g.make<FieldDescriptorProto>(18, g.or_subclass));
  fp.mutable_message_type(0)->mutable_field(0)->set_oneof_index(
    *g.make<int32_t>(19));
  fp.mutable_message_type(0)->mutable_oneof_decl()->AddAllocated(
    g.make<OneofDescriptorProto>(20));
  return g.make<DescriptorPool>(21)
    ->BuildFile(fp)
    ->message_type(0)
    ->field(0)
    ->containing_oneof();
}

const EnumValueDescriptor* makeEnumVal(gen& g)
{
  EnumDescriptorProto ep;
  ep.mutable_value()->AddAllocated(g.make<EnumValueDescriptorProto>(22));
  FileDescriptorProto fp;
  fp.mutable_enum_type()->AddAllocated(
    g.make<EnumDescriptorProto>(23, g.or_subclass));
  return g.make<DescriptorPool>(24)->BuildFile(fp)->enum_type(0)->value(0);
}

} // anonymous namespace

namespace ramfuzz {

harness<Descriptor>::harness(runtime::gen& g)
  : g(g), obj(const_cast<Descriptor*>(makeDesc(g)))
{
}

harness<FieldDescriptor>::harness(runtime::gen& g)
  : g(g), obj(const_cast<FieldDescriptor*>(makeField(g)))
{
}

harness<OneofDescriptor>::harness(runtime::gen& g)
  : g(g), obj(const_cast<OneofDescriptor*>(makeOneof(g)))
{
}

harness<EnumValueDescriptor>::harness(runtime::gen& g)
  : g(g), obj(const_cast<EnumValueDescriptor*>(makeEnumVal(g)))
{
}

harness<FileDescriptor>::harness(runtime::gen& g)
  : g(g), obj(const_cast<FileDescriptor*>(makeFileDesc(g)))
{
}

} // namespace ramfuzz
