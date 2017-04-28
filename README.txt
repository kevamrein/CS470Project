-- Title --
Analysis of Parallel Implementations of Centrality Algorithms 

-- Authors --
Kevin Amrein, Sam Carswell, and Chuchi Soriano

-- Source Code --
setup.sh has the code to preload the igraph library and use gcc v.4. 

/bc_dil holds the source code for the OMP implementations of BC and DIL. 
	- bc_omp.c: source code for betweenness centrality
	- dil_omp.c: source code for degree & line importance
	- data directory: contains datasets used for testing 
      (formatted as edge lists)

/ec holds the source code for the serial and OMP implementation of EC.
	- AdjacencyMatrixConverter: Java program that converts a file containing
      edge lists to a file containing an adjacency matrix to be passed when 
      running the implementation for EC. 
    - ec_serial.c: source code for serial implementation of EC 
    - ec_par.c: source code for parallel implementation of EC 
	- data directory: contains preconverted adjacency matrices used for testing
	- out directory: stores output files used, when ran directory's test.sh

Disregard /igraph_example: folder of tutorial code for IGraph library

-- Project Directions --
1. $ . ./setup.sh 

2. $ srun ./test.sh
This script tests EC, BC, and DIL with 3 datasets for accuracy: ability to
find important nodes. (explanation of output in final report)
This also tests BC and DIL with 2 datasets for performance. EC was not run
due to its extremely long execution time (~hours).

--
-- bc_dil/data text file format -- 
    
    2       # of Edges * 2
    0 1     FromVertex ToVertex

-- ec/utilities/AdjancenyMatrixConverter Directions -- 
1. $ java AdjancencyMatrixConverter EDGELISTFILE #OFNODES <data/OUTPUTFILENAME>
