#!/usr/bin/env bash

./create-experiment-folder.sh experiment6-2
cd experiment6-2
cp ../utilities/runlarge.sh run.sh
cp ../patterns/k4.gr pattern/
./prepare.sh k4
python3 rungen.py 5 20 1 0.0001 10000 10
