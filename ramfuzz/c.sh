#!/bin/bash

MI=~/src/mesos/include
MB=~/src/mesos/build
MBI=$MB/include
PM=$MBI/mesos
PB=$MB/3rdparty/protobuf-2.6.1/src
GP=$PB/google/protobuf
RF=~/src/ramfuzz
INC="-I$MI -I$MBI -I$PB -I$RF/runtime"


c++ -std=c++11 -g $INC \
    ${1:-main.cpp} missimpl.cpp fuzz.cpp $RF/runtime/ramfuzz-rt.cpp \
    /usr/local/lib/libmesos-1.1.0.dylib
