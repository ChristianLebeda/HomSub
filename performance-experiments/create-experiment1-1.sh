#!/usr/bin/env bash

./create-experiment-folder.sh experiment1-1
cp patterns/k3.gr experiment1-1/pattern
cd experiment1-1
./prepare.sh k3
python3 rungen.py 50 300 25 0.001 1000 10
rm input/0.2000/*.grf
rm input/0.2250/*.grf
rm input/0.2500/*.grf
rm input/0.2750/*.grf
rm input/0.3000/*.grf
