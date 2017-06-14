#!/bin/bash

MI=~/src/mesos/include
MB=~/src/mesos/build
MBI=$MB/include
PM=$MBI/mesos
PB=$MB/3rdparty/protobuf-3.3.0/src
GP=$PB/google/protobuf
BOO=$MB/3rdparty/boost-1.53.0
GL=$MB/3rdparty/glog-0.3.3/src
PJ=$MB/3rdparty/picojson-1.3.0
STO=~/src/mesos/3rdparty/stout/include
INC="-I$MI -I$MBI -I$PB -I$BOO -I$STO -I$GL -I$PJ"

~/src/lb/bin/ramfuzz \
    $GP/arena.h \
    $GP/descriptor.h \
    $GP/descriptor.pb.h \
    $GP/descriptor_database.h \
    $GP/io/coded_stream.h \
    $GP/io/zero_copy_stream.h \
    $GP/message.h \
    $GP/message_lite.h \
    $GP/unknown_field_set.h \
    $MI/mesos/resources.hpp \
    $PM/mesos.pb.h \
    -- -xc++ -std=c++11 $INC

echo '#include <google/protobuf/io/coded_stream_inl.h>' >> fuzz.cpp
