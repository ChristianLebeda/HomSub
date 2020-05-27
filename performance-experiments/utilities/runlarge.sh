#!/usr/bin/env bash

if [ "$#" -ne 1 ]; then
    echo "Type pattern name as argument"
    exit 1
fi

mkdir -p output/

echo "Using pattern/$1 as H"

#Run homlib
for i in input/*/*.gr; do
  echo "homlib $i"
  time(
    echo "Homlib $i"
    python3 ~/Downloads/homlib/example/run.py pattern/$1.gr $i &>> output/homlib.csv
  ) &>> output/homlib.log
done

# Run VF3 algorithm
for i in input/*/*.grf; do
  echo "vf3 $i"
  time(
      echo "vf3 $i"
      printf "vf3,$i," &>> output/vf3.out
      ~/Desktop/vf3lib/bin/vf3 pattern/$1.grf $i -u &>> output/vf3.out
      echo "" &>> output/vf3.out
  ) &>> output/vf3.log
done

# Run glasgow algorithm
for i in input/*/*.lad; do
  echo "Glasgow $i"
  time(
    echo "Glasgow $i"
    echo "glasgow,$i," &>> output/glasgow.out
    ~/Downloads/glasgow-subgraph-solver/glasgow_subgraph_solver --format=lad --count-solutions pattern/$1.lad $i &>> output/glasgow.out
    echo "" &>> output/glasgow.out
  ) &>> output/glasgow.log
done
