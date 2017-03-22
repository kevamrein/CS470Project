default: vertex betweenness graph

test: graph
	LD_PRELOAD=/shared/lib/igraph-0.7.1/src/.libs/libigraph.so ./graph edges.txt 

vertex: vertex.c
	gcc vertex.c -I/shared/lib/igraph-0.7.1/include -L/shared/lib/igraph-0.7.1/src/.libs -ligraph -o vertex

betweenness: edge_betweenness.c
	gcc edge_betweenness.c -I/shared/lib/igraph-0.7.1/include -L/shared/lib/igraph-0.7.1/src/.libs -ligraph -o betweenness 

graph: graph.c
	gcc graph.c -I/shared/lib/igraph-0.7.1/include -L/shared/lib/igraph-0.7.1/src/.libs -ligraph -o graph

clean:
	rm -f vertex betweenness
