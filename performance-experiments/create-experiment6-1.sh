#!/usr/bin/env bash

./create-experiment-folder.sh experiment6-1
cd experiment6-1
cp ../utilities/runlarge.sh run.sh
cp ../patterns/hourglass.gr pattern/
cp ../patterns/homlibhourglass/*.gr pattern/
./prepare.sh hourglass
python3 rungen.py 10 25 1 0.0001 10000 10
rm input/0.0020/*.grf
rm input/0.0021/*.grf
rm input/0.0022/*.grf
rm input/0.0023/*.grf
rm input/0.0024/*.grf
rm input/0.0025/*.grf
