#!/usr/bin/env bash

if [ "$#" -ne 1 ]; then
    echo "Type pattern name as argument"
    exit 1
fi

mkdir -p output/

echo "Using pattern/$1 as H"

# Run treewidth algorithm
for i in input/*/*.gr; do
  echo "Treewidth $i"
  time(
    echo "Treewidth $i"
    ../../experiments-build/experiments/experiments -runTimed -h pattern/$1.spsmd -g $i &>> output/treewidth.csv
  ) &>> output/treewidth.log
done

for i in input/*/*.gr; do
  echo "homlib $i"
  time(
    echo "Homlib $i"
    python3 runhomlib.py pattern/$1.gr $i &>> output/homlib.csv
  ) &>> output/homlib.log
done
