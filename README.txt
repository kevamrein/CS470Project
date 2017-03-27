-- Title --
Graph Analysis 

-- Authors --
Kevin Amrein, Sam Carswell, and Chuchi Soriano

-- Source Code --
setup.sh has the code to preload the igraph library and use gcc v.4. 

/betweenness holds the source code for the OMP implementations of BC and DIL. 
	- bc_omp.c: source code for betweenness centrality with omp pragmas
	- dil_omp.c: source code for degree & line importance w/ omp pragmas
	- data directory: contains zachary's karate data set & simple networks 

/eigenvalue holds the source code for the serial implementation of EC.
	- ec_serial.c: source code for serial implementation of EC 
	- data directory: contains example adjacency matrices for 1 community
	- out directory: stores output files

Disregard /igraph_example: folder of tutorial code for IGraph library

--  Directions --
1. Run ./setup.sh 
(We ran into some issues with the script not loading the required files so 
if errors occurs, make sure to run these commands first): 
	1. export LD_LIBRARY_PATH=/shared/lib/igraph-0.7.1/build/lib:$LD_LIBRARY_PATH
	2. source /shared/bin/gcc-4.9.4-setup.sh

To test BC & DIL: 
	1. From the parent directory, Run cd betweenness/
	2. Run ./test.sh to see the results for BC and DIL
(If test.sh is run with sbatch or srun, there are errors at the top related to the
custom reduction. We believe there's an issue with correct gcc compiler not being 
sourced on the compute nodes) 

To test EC: 
	1. From the parent directory, Run cd eigenvalue/
	2. Run ./test.sh to see the results for EC w/ multiple adjacency matrices
	3. Run cd out/ to see the results for different adjacency matrices
