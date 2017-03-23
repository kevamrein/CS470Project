CLUSTER_LDFLAG=-L/shared/lib/igraph-0.7.1/build/lib
CLUSTER_CFLAG=-I/shared/lib/igraph-0.7.1/build/include/igraph
LDFLAG=-L/usr/local/Cellar/igraph/0.7.1_3/lib
CFLAG=-I/usr/local/Cellar/igraph/0.7.1_3/include/igraph

default: graph omp

cluster: graph-cluster.o omp-cluster.o
	gcc $(CLUSTER_CFLAG) $(CLUSTER_LDFLAG) -fopenmp -ligraph -o proj graph.o community_center_omp.o

graph: graph.c
	gcc -c graph.c $(CFLAG) $(LDFLAG) -ligraph -o graph

graph-cluster.o: graph.h graph.c
	gcc -c $(CLUSTER_CFLAG) $(CLUSTER_LDFLAG) -ligraph graph.c

omp-cluster.o: graph.h community_center_omp.c
	gcc -c $(CLUSTER_CFLAG) $(CLUSTER_LDFLAG) -fopenmp -ligraph community_center_omp.c

omp: community_center_omp.c
	gcc -c community_center_omp.c $(CFLAG) $(LDFLAG) -ligraph -o community_center_omp 

clean:
	rm -f graph.o community_center_omp.o proj
