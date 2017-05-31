#!/bin/bash

MI=~/src/mesos/include
MB=~/src/mesos/build
MBI=$MB/include
PM=$MBI/mesos
PB=$MB/3rdparty/protobuf-2.6.1/src
GP=$PB/google/protobuf
INC="-I$MI -I$MBI -I$PB"

~/src/lb/bin/ramfuzz \
    $GP/descriptor.h \
    $GP/descriptor.pb.h \
    $GP/descriptor_database.h \
    $GP/io/coded_stream.h \
    $GP/io/zero_copy_stream.h \
    $GP/message.h \
    $GP/message_lite.h \
    $GP/unknown_field_set.h \
    $MI/mesos/scheduler.hpp \
    $PM/mesos.pb.h \
    -- -xc++ -std=c++11 $INC

echo '#include <google/protobuf/io/coded_stream_inl.h>' >> fuzz.cpp
