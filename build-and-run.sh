#!/usr/bin/env bash

BUIILDDIR="experiments-build"
mkdir -p $BUIILDDIR
cd $BUIILDDIR
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
cd ..

./run-and-save-result.sh $BUIILDDIR"/experiments/experiments" $@
