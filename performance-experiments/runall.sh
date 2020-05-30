#!/usr/bin/env bash

cd experiment1-1
time ./run.sh k3
python3 convertresults.py treewidth vf3 glasgow
cd ..

cd experiment1-2
time ./run.sh k4
python3 convertresults.py treewidth vf3 glasgow
cd ..

cd experiment1-3
time ./run.sh k5
python3 convertresults.py treewidth vf3 glasgow
cd ..

cd experiment2-1
time ./run.sh hourglass
python3 convertresults.py treewidth vf3 glasgow
cd ..

cd experiment2-2
time ./run.sh hourglass
python3 convertresults.py treewidth vf3 glasgow
cd ..

cd experiment3-1
time ./run.sh triangles
python3 convertresults.py treewidth vf3 glasgow
cd ..

cd experiment3-2
time ./run.sh triangles
python3 convertresults.py treewidth vf3 glasgow
cd ..

cd experiment4-1
time ./run.sh cycle7
python3 convertresults.py treewidth homlib
cd ..

cd experiment4-2
time ./run.sh cycle7
python3 convertresults.py treewidth homlib
cd ..

cd experiment5-1
time ./run.sh sp9
python3 convertresults.py treewidth homlib
cd ..

cd experiment5-2
time ./run.sh sp9
python3 convertresults.py treewidth homlib
cd ..

cd experiment6-1
time ./run.sh hourglass
python3 convertresults.py homlib vf3 glasgow
cd ..

cd experiment6-2
time ./run.sh k4
python3 convertresults.py homlib vf3 glasgow
cd ..
