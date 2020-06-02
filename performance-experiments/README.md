# Performance experiments

This folder contains scripts to replicate the performance experiments presented in the chapter "Comparison with available implementations" of our report. 

To run these example you need to clone and build the repositories for VF3, the Glasgow Subgraph Solver and homlib.

The scripts using the settings used for the report. 

Exeriements:
 - 1-1: 3-clique random graphs n=1000
 - 1-2: 4-clique random graphs n=150
 - 1-3: 5-clique random graphs n=60
 - 2-1: dragonfly random graphs n=1000 
 - 2-2: dragonfly random graphs n=500
 - 3-1: triangle-path random graphs n=150 
 - 3-2: triangle-path random graphs n=75
 - 4-1: 7-cycles homomorphisms random graphs n=1000 
 - 4-2: 7-cycles homomorphisms random graphs n=500
 - 5-1: bunker homomorphisms random graphs n=150 
 - 5-2: bunker homomorphisms random graphs n=75
 - 6-1: dragonfly homomorphisms random graphs n=10000
 - 6-2: 4-clique homomorphisms random graphs n=10000

To create the experiments with the same settings used for the report use

```
 ./createall
```

To run all experiments

```
 ./runall
```
