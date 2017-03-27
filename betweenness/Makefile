CLUSTER_LDFLAG=-L/shared/lib/igraph-0.7.1/build/lib
CLUSTER_CFLAG=-I/shared/lib/igraph-0.7.1/build/include/igraph

default: graph-cluster.o bc-cluster.o dil-cluster.o
	gcc $(CLUSTER_CFLAG) $(CLUSTER_LDFLAG) -fopenmp -ligraph -o bc graph.o bc_omp.o
	gcc $(CLUSTER_CFLAG) $(CLUSTER_LDFLAG) -fopenmp -ligraph -o dil graph.o dil_omp.o

graph-cluster.o: graph.h graph.c
	gcc -c $(CLUSTER_CFLAG) $(CLUSTER_LDFLAG) -ligraph graph.c

bc-cluster.o: graph.h bc_omp.c
	gcc -c $(CLUSTER_CFLAG) $(CLUSTER_LDFLAG) -fopenmp -ligraph bc_omp.c

dil-cluster.o: graph.h dil_omp.c
	gcc -c $(CLUSTER_CFLAG) $(CLUSTER_LDFLAG) -fopenmp -ligraph dil_omp.c

clean:
	rm -f *.o bc dil
