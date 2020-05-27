#!/usr/bin/env bash

./create-experiment-folder.sh experiment2-1
cd experiment2-1
cp ../patterns/hourglass.gr pattern/
./prepare.sh hourglass
python3 rungen.py 17 25 1 0.001 1000 5
