#!/usr/bin/env bash

./create-experiment-folder.sh experiment2-2
cd experiment2-2
cp ../patterns/hourglass.gr pattern/
./prepare.sh hourglass
python3 rungen.py 23 37 1 0.001 500 10
