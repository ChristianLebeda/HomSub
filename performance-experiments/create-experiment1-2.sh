#!/usr/bin/env bash

./create-experiment-folder.sh experiment1-2
cp patterns/k4.gr experiment1-2/pattern
cd experiment1-2
./prepare.sh k4
python3 rungen.py 250 700 25 0.001 150 10
rm input/0.550/*.grf
rm input/0.575/*.grf
rm input/0.600/*.grf
rm input/0.625/*.grf
rm input/0.650/*.grf
rm input/0.675/*.grf
rm input/0.700/*.grf
