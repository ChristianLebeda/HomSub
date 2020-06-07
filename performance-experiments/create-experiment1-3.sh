#!/usr/bin/env bash

./create-experiment-folder.sh experiment1-3
cd experiment1-3
cp ../patterns/k5.gr pattern/
./prepare.sh k5
python3 rungen.py 400 800 25 0.001 60 10
rm input/0.7500/*.grf
rm input/0.7750/*.grf
rm input/0.8000/*.grf
