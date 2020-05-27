#!/usr/bin/env bash

./create-experiment-folder.sh experiment3-2
cd experiment3-2
cp ../patterns/triangles.gr pattern/
./prepare.sh triangles
python3 rungen.py 100 140 5 0.001 75 10
