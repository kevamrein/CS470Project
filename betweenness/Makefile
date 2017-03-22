default: graph

cluster: graph-cluster

test: graph-cluster
	LD_PRELOAD=/shared/lib/igraph-0.7.1/src/.libs/libigraph.so ./graph edges.txt 

graph: graph.c
	gcc graph.c -I/usr/local/Cellar/igraph/0.7.1_3/include/igraph -L/usr/local/Cellar/igraph/0.7.1_3/lib -ligraph -o graph

graph-cluster: graph.c
	gcc graph.c -I/shared/lib/igraph-0.7.1/build/include/igraph -L/shared/lib/igraph-0.7.1/build/lib -ligraph -o graph

clean:
	rm -f graph
