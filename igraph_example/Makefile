default: vertex betweenness

cluster: vertex-cluster betweenness-cluster

vertex: vertex.c
	gcc vertex.c -I/usr/local/Cellar/igraph/0.7.1_3/include/igraph -L/usr/local/Cellar/igraph/0.7.1_3/lib -ligraph -o vertex

betweenness: edge_betweenness.c
	gcc edge_betweenness.c -I/usr/local/Cellar/igraph/0.7.1_3/include/igraph -L/usr/local/Cellar/igraph/0.7.1_3/lib -ligraph -o betweenness

betweenness-cluster: edge_betweenness.c
	gcc edge_betweenness.c -I/shared/lib/igraph-0.7.1/build/include/igraph -L/shared/lib/igraph-0.7.1/build/lib -ligraph -o betweenness

vertex-cluster: vertex.c
	gcc vertex.c -I/shared/lib/igraph-0.7.1/build/include/igraph -L/shared/lib/igraph-0.7.1/build/lib -ligraph -o vertex

clean:
	rm -f vertex betweenness
