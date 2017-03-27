## Title
Graph Analysis 

## Authors
Kevin Amrein, Sam Carswell, and Chuchi Soriano

## Source Code
setup.sh has the code to preload the igraph library and use the gcc v.4. 

/betweenness folder holds the source code for the serial and parallel 
	implementations of BC and DIL. 
	- bc_omp.c : source code for betweenness centrality with omp pragmas
	- dil_omp.c : source code for degree & line importance w/ omp pragmas
	- data directory: contains zach's data set & simple networks 

/eigenvalue folder holds the source code for the serial implementation of EC.
	- ec_serial : source code for serial implementation of EC 
	- data directory : contains example adjacency matrices for 1 community
	- out directory : stores output files

## Directions

Run setup.sh

To test BC & DIL: 
	1. Go to betweenness directory
	2. Run test.sh to see the results for BC and DIL

To test EC: 
	1. Go to the eigenvalues folder
	2. Run test.sh to see the results for EC w/ multiple adjacency matrices
