#include <igraph.h>

int main() {
    igraph_t g;
    igraph_vit_t vit;

    igraph_small(&g, 0, IGRAPH_UNDIRECTED, 0, 1, 1, 2, 1, 3, 2, 3, 2, 4, 4, 6, 5, 6, 5,
        7, 6, 8, 7, 10, 7, 8, 8, 10, 8, 9, 8, 11, -1);

    igraph_vit_create(&g, igraph_vss_all(), &vit);
    printf("Size: %ld\n\n", IGRAPH_VIT_SIZE(vit));
    while (!IGRAPH_VIT_END(vit)) {
        printf("%li\n", (long int) IGRAPH_VIT_GET(vit));
        IGRAPH_VIT_NEXT(vit);
    }

    igraph_vit_destroy(&vit);
    igraph_destroy(&g);
}
