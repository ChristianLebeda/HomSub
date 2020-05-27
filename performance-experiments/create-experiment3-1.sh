#!/usr/bin/env bash

./create-experiment-folder.sh experiment3-1
cd experiment3-1
cp ../patterns/triangles.gr pattern/
./prepare.sh triangles
python3 rungen.py 60 100 5 0.001 150 5
