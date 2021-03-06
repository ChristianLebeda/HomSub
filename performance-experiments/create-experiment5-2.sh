#!/usr/bin/env bash

./create-experiment-folder.sh experiment5-2
cd experiment5-2
cp ../utilities/runhomomorphisms.sh run.sh
cp ../patterns/sp9.gr pattern/
./prepare.sh sp9
python3 ../utilities/trimspasm.py pattern/sp9.spsmd > tmp
mv tmp pattern/sp9.spsmd
python3 rungen.py 200 350 25 0.001 75 10
rm input/*/*.grf
rm input/*/*.lad
