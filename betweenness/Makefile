CLUSTER_LDFLAG=-L/shared/lib/igraph-0.7.1/build/lib
CLUSTER_CFLAG=-I/shared/lib/igraph-0.7.1/build/include/igraph
LDFLAG=-L/usr/local/Cellar/igraph/0.7.1_3/lib
CFLAG=-I/usr/local/Cellar/igraph/0.7.1_3/include/igraph

default: graph omp

cluster: app

app: community_center_omp.o graph.o
	gcc community_center_omp.o graph.o -o app

graph: graph.c
	gcc -c graph.c $(CFLAG) $(LDFLAG) -ligraph -o graph

graph-cluster.o: graph.c graph.h
	gcc -c graph.c $(CLUSTER_CFLAG) $(CLUSTER_LDFLAG) -ligraph -o graph.o

omp-cluster.o: community_center_omp.c graph.h
	gcc -c community_center_omp.c $(CLUSTER_CFLAG) $(CLUSTER_LDFLAG) -ligraph -o community_center_omp.o

omp: community_center_omp.c
	gcc -c community_center_omp.c $(CFLAG) $(LDFLAG)  -o community_center_omp 

clean:
	rm -f graph community_center_omp
