default: vertex betweenness

vertex: vertex.c
	gcc vertex.c -I/usr/local/Cellar/igraph/0.7.1_3/include/igraph -L/usr/local/Cellar/igraph/0.7.1_3/lib -ligraph -o vertex

betweenness: edge_betweenness.c
	gcc edge_betweenness.c -I/usr/local/Cellar/igraph/0.7.1_3/include/igraph -L/usr/local/Cellar/igraph/0.7.1_3/lib -ligraph -o betweenness 

clean:
	rm -f vertex betweenness
