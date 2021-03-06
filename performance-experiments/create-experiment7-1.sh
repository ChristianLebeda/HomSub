#!/usr/bin/env bash

./create-experiment-folder.sh experiment7-1
cd experiment7-1
cp ../utilities/runhomomorphisms.sh run.sh
cp ../patterns/cycle7.gr pattern/
./prepare.sh cycle7
python3 ../utilities/trimspasm.py pattern/cycle7.spsmd > tmp
mv tmp pattern/cycle7.spsmd
python3 rungen.py 2 15 1 0.001 1000 5
rm input/*/*.grf
rm input/*/*.lad
