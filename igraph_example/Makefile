default: vertex betweenness graph

cluster: graph-cluster vertex-cluster betweenness-cluster

test: graph
	LD_PRELOAD=/shared/lib/igraph-0.7.1/src/.libs/libigraph.so ./graph edges.txt 

vertex: vertex.c
	gcc vertex.c -I/usr/local/Cellar/igraph/0.7.1_3/include/igraph -L/usr/local/Cellar/igraph/0.7.1_3/lib -ligraph -o vertex

betweenness: edge_betweenness.c
	gcc edge_betweenness.c -I/usr/local/Cellar/igraph/0.7.1_3/include/igraph -L/usr/local/Cellar/igraph/0.7.1_3/lib -ligraph -o betweenness

graph: graph.c
	gcc graph.c -I/usr/local/Cellar/igraph/0.7.1_3/include/igraph -L/usr/local/Cellar/igraph/0.7.1_3/lib -ligraph -o graph

betweenness-cluster: edge_betweenness.c
	gcc edge_betweenness.c -I/shared/lib/igraph-0.7.1/build/include/igraph -L/shared/lib/igraph-0.7.1/build/lib -ligraph -o betweenness

vertex-cluster: vertex.c
	gcc vertex.c -I/shared/lib/igraph-0.7.1/build/include/igraph -L/shared/lib/igraph-0.7.1/build/lib -ligraph -o vertex

graph-cluster: graph.c
	gcc graph.c -I/shared/lib/igraph-0.7.1/build/include/igraph -L/shared/lib/igraph-0.7.1/build/lib -ligraph -o graph

clean:
	rm -f vertex betweenness graph
