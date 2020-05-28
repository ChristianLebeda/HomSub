#!/usr/bin/env bash

if [ "$#" -ne 4 ]; then
    echo "Type edge count as argument"
    exit 1
fi

mkdir -p input/$3
cd input/$3
../../../../build/experiments/experiments -seed $1 -genGraph $2 -edgeProbability $3 -rep $4 > graphs.gr
python3 ../../splitgraphs.py graphs.gr
rm graphs.gr

a=1
for i in *.gr; do
  gr=$(printf "$3-%02d.gr" "$a") 
  grf=$(printf "$3-%02d.grf" "$a")
  lad=$(printf "$3-%02d.lad" "$a")
  mv -i -- "$i" "$gr"
  python3 ../../convertgrtogrf.py "$gr" > "$grf"
  python3 ../../convertgrtolad.py "$gr" > "$lad"
  let a=a+1
done

