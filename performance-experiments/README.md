# Performance experiments

This folder contains scripts to replicate the performance experiments presented in the chapter "Comparison with available implementations" of our report. 

To run these example you need to clone and build the repositories for VF3, the Glasgow Subgraph Solver and homlib.

Before running the scripts replace the path to VF3 and the glasgow subgraph solver in the *runexperiment* and *runlarge* files in the utility folder.

The experiments ran on a machine using Ubuntu 18-04 LTS.  
Python3 is required.

The scripts uses the settings detailed in the report.  
Some of the experiments are not shown in the report. These are marked with an asterisk.

Exeriements:
 - 1-1: 3-clique random graphs n=1000
 - 1-2: 4-clique random graphs n=150
 - 1-3: 5-clique random graphs n=60
 - 2-1: dragonfly random graphs n=1000 
 - 2-2: dragonfly random graphs n=500
 - 3-1: triangle-path random graphs n=150 
 - 3-2: triangle-path random graphs n=75
 - 4-1: 7-cycles homomorphisms random graphs n=1000 
 - 4-2: 7-cycles homomorphisms random graphs n=500 *
 - 5-1: bunker homomorphisms random graphs n=150 
 - 5-2: bunker homomorphisms random graphs n=75 *
 - 6-1: dragonfly homlib random graphs n=10000
 - 6-2: 4-clique homlib random graphs n=10000
 - 7-1: 7-cycle homlib memory comparison random graphs n=1000 *
 - 7-2: 7-cycle homlib memory comparison random graphs n=500
 - 7-3: bunker homlib memory comparison random graphs n=150

To create all experiments use

```
 ./createall
```

To run all experiments use

```
 ./runall
```
