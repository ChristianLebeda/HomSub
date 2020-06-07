#!/usr/bin/env bash

./create-experiment-folder.sh experiment1-2
cp patterns/k4.gr experiment1-2/pattern
cd experiment1-2
./prepare.sh k4
python3 rungen.py 250 700 25 0.001 150 10
rm input/0.5500/*.grf
rm input/0.5750/*.grf
rm input/0.6000/*.grf
rm input/0.6250/*.grf
rm input/0.6500/*.grf
rm input/0.6750/*.grf
rm input/0.7000/*.grf
