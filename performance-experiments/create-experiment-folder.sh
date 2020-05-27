#!/usr/bin/env bash

mkdir -p $1/input
mkdir -p $1/pattern
cp utilities/convertgrtogrf.py $1/
cp utilities/convertgrtolad.py $1/
cp utilities/convertresults.py $1/
cp utilities/splitgraphs.py $1/
cp utilities/rungen.py $1/
cp utilities/gen.sh $1/
cp utilities/prepare.sh $1/
cp utilities/runexperiment.sh $1/run.sh
