default: vertex betweenness graph test

vertex: vertex.c
	gcc vertex.c -I/usr/local/Cellar/igraph/0.7.1_3/include/igraph -L/usr/local/Cellar/igraph/0.7.1_3/lib -ligraph -o vertex

betweenness: edge_betweenness.c
	gcc edge_betweenness.c -I/usr/local/Cellar/igraph/0.7.1_3/include/igraph -L/usr/local/Cellar/igraph/0.7.1_3/lib -ligraph -o betweenness 

graph: graph.c
	gcc graph.c -I/usr/local/Cellar/igraph/0.7.1_3/include/igraph -L/usr/local/Cellar/igraph/0.7.1_3/lib -ligraph -o graph

test: test.c
	gcc test.c -I/usr/local/Cellar/igraph/0.7.1_3/include/igraph -L/usr/local/Cellar/igraph/0.7.1_3/lib -ligraph -o test


clean:
	rm -f vertex betweenness
