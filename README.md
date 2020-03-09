# Thesis - Counting subgraphs

This is the repository used for the thesis of Christian Janos Lebeda and Jonas Mortensen under the supervision of Radu-Cristian Curticapean and Holger Dell.

The repository contains two projects.

The first will include an implementation of the algorithm for counting subgraphs described in the research paper [Homomorphisms Are a Good Basis for Counting Small Subgraphs](https://arxiv.org/abs/1705.01595).

The second project will be used for conducting performance experiments of said implementation.

## Building and compiling

The project uses two third party libraries. These are included as submodules of the repository. To build them run the following commands.

```
git submodule init
git submodule update
sh build-third-party.sh
```

To create a CMake project run.

```
mkdir build
cd build
cmake ..
```
