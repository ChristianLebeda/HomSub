#!/usr/bin/env bash

BUIILDDIR="experiments-build"
mkdir -p $BUIILDDIR
cd $BUIILDDIR
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
cd ..