#include <igraph.h>

int main() {
    igraph_t g;
    igraph_vit_t vit;

    igraph_small(&g, 0, IGRAPH_UNDIRECTED, 0, 1, 1, 2, 1, 3, 2, 3, 2, 4, 4, 6, 5, 6, 5,
        7, 6, 8, 7, 10, 7, 8, 8, 10, 8, 9, 8, 11, -1);

    // Create an vit (iterator) through all of the vertices
    igraph_vit_create(&g, igraph_vss_all(), &vit);

    // Get the amount of items in the iterator
    printf("Size: %ld\n\n", IGRAPH_VIT_SIZE(vit));

    // Loop through each vertex in the iterator and print its id (CH. 5)
    while (!IGRAPH_VIT_END(vit)) {
        printf("%li\n", (long int) IGRAPH_VIT_GET(vit));
        IGRAPH_VIT_NEXT(vit);
    }

    igraph_vs_t vertices;
    igraph_vit_t vertexIter;
    // Create a vector with vertices from 0 - 8 inclusive
    igraph_vs_seq(&vertices, 0, 8);

    // Create the interator from this vector
    igraph_vit_create(&g, vertices, &vertexIter);

    // Loop through each vertex in the iterator and print its id (0-8 inclusive)
    while (!IGRAPH_VIT_END(vertexIter)) {
        printf("%li\n", (long int) IGRAPH_VIT_GET(vertexIter));
        IGRAPH_VIT_NEXT(vertexIter);
    }

    // Destroy all resources
    igraph_vs_destroy(&vertices);
    igraph_vit_destroy(&vertexIter);
    igraph_vit_destroy(&vit);
    igraph_destroy(&g);
}
