CLUSTER_LDFLAG=-L/shared/lib/igraph-0.7.1/build/lib
CLUSTER_CFLAG=-I/shared/lib/igraph-0.7.1/build/include/igraph

default: eigenvalue_centrality_serial

eigenvalue_centrality_serial: eigenvalue_centrality_serial.c
	gcc eigenvalue_centrality_serial.c  $(CLUSTER_CFLAG) $(CLUSTER_LDFLAG) -ligraph -o eigenvalue_centrality_serial

clean:
	rm -f eigenvalue_centrality_serial
