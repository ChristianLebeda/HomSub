#!/usr/bin/env bash

./create-experiment-folder.sh experiment7-3
cd experiment7-3
cp ../utilities/runhomomorphismmemory.sh run.sh
cp ../patterns/sp9.gr pattern/
./prepare.sh sp9
python3 ../utilities/trimspasm.py pattern/sp9.spsmd > tmp
mv tmp pattern/sp9.spsmd
python3 rungen.py 300 600 25 0.001 150 5
rm input/*/*.grf
rm input/*/*.lad
