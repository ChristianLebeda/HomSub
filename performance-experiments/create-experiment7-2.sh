#!/usr/bin/env bash

./create-experiment-folder.sh experiment7-2
cd experiment7-2
cp ../utilities/runhomomorphismmemory.sh run.sh
cp ../patterns/cycle7.gr pattern/
./prepare.sh cycle7
python3 ../utilities/trimspasm.py pattern/cycle7.spsmd > tmp
mv tmp pattern/cycle7.spsmd
python3 rungen.py 10 70 5 0.001 500 10
rm input/*/*.grf
rm input/*/*.lad
