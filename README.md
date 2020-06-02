# HomSub: Counting small subgraphs via homomorphisms

This is the repository used for the thesis of Christian Janos Lebeda and Jonas Mortensen under the supervision of Radu-Cristian Curticapean and Holger Dell.

The repository contains two projects.

The first is an implementation of the algorithm for counting small subgraphs described in the research paper [Homomorphisms Are a Good Basis for Counting Small Subgraphs](https://arxiv.org/abs/1705.01595).

The second project is used for conducting performance experiments of said implementation.

## Building and running

The project uses two third party libraries. These are included as submodules of the repository. To build them run the following commands.

```shell
git submodule init
git submodule update
sh build-third-party.sh
```
Run the `build-and-run` script to run all performance experiments and log the results in the ExperimentsResults directory.

Run the `build` script to create an executable in the folder `experiments-build/experiments` which can be used to run the algorithm on an input pattern and host graph (.gr file): `./experiments -count -h <pattern file> -g <host file>`

## File types

The project uses a number of different files formats.  

### .gr and .td  

These formats are used to compute and store tree decompositions. They are explained in the repository for the [PACE treewidth challenge](https://github.com/PACE-challenge/Treewidth).  

### Spasm serialization

A spasm is serialized in the following format. The first line contains the string sp, following by the C the number of graphs in the spasm and N and M the number of vertices and edges in the original graph. The next line contains the graph6 format of the original graph. The following C lines contains a number and a string. The number is the coefficient of the graph described by the string as graph6 format. Below is an example of the format for a square. All graphs are on a canonical labeled form.  

```text
sp 3 4 4
Cl
1 Cr
-2 BW
1 A_
```

Additionally the extended version of a spasm that includes tree decompositions for all graphs includes an addition number on the first line depicting the maximum treewidth of the tree decompositions. At the end of the file the C tree decompositions are stored in the .td format. The example below is the spasm including decompositions for a square.  

```text
sp 3 4 4 2
Cl
1 Cr
-2 BW
1 A_
s td 2 3 4
b 1 3 1 2
b 2 4 2 3
1 2
s td 3 2 3
b 1 3 1
b 2 3 2
b 3 3
1 3
2 3
s td 1 2 2
b 1 2 1
```

We have compared HomSub to existing software for counting homomorphisms and for counting subgraphs (both induced and non-induced). Here we include links to the state of the repositories at the time of comparison:
- [The Glashow Subgraph Solver](https://github.com/ciaranm/glasgow-subgraph-solver/tree/b3fe447c619abb6dd10d67ed8fc50627d1dc25d7) (Counting non-induced subgraphs)
- [VF3](https://github.com/MiviaLab/vf3lib/tree/130cf1036596e136f7565f6142f901c46844651b) (Counting induced subgraphs)
- [Homlib](https://github.com/spaghetti-source/homlib/tree/534d900b35fea549958dc72473defdffef81a8) (Counting homomorphisms)
