#!/usr/bin/env bash

if [ "$#" -ne 1 ]; then
    echo "Type pattern name as argument"
    exit 1
fi

python3 convertgrtogrf.py pattern/$1.gr > pattern/$1.grf
python3 convertgrtolad.py pattern/$1.gr > pattern/$1.lad
../../build/experiments/experiments -spasm -in pattern/$1.gr -out pattern/$1.spsm
../../build/experiments/experiments -spasmdecomp -in pattern/$1.gr -out pattern/$1.spsmd


