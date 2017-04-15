/**
 * dil_omp.c contains a parallelized implementation of the Degree and 
 * Line Importance algorithm for finding important nodes in a graph.
 * The functions are broken up so that each calculation has its own
 * function along with some helpers.
 */

#include <stdbool.h>
#include "graph.h"
#ifdef _OPENMP
#include <omp.h>
#endif

#define DEGREE_VECTOR_SIZE 2
#define P_VALUE 0
igraph_t graph;

// Function prototypes
double get_importance(struct edge *current);
double get_u(struct edge *current);
double get_lambda(int p_value);
double get_w(struct edge *current);
double get_l(int vid);
struct edge build_edge(int from, int to);
double get_vertex_degree(int vid);

typedef struct Compare {
    double l_value;
    int vid;
} Compare;

/**
 * Gets the L-Value for each vertex and prints the max value and the
 * corresponding vertex.
 */
int main(int argc, char* argv[]) {
    // Create graph
    graph = create_graph(argv[1]);
    
    int vcount = igraph_vcount(&graph);
    int i;
    struct Compare max_info;

    max_info.l_value = -1;
    max_info.vid = -1;
 
#   pragma omp declare reduction(maximum : struct Compare : \
    omp_out = omp_in.l_value < omp_out.l_value ? omp_out : omp_in)

    START_TIMER(max_count)
#   pragma omp parallel for default(none) shared (vcount)  private(i) \
    reduction (maximum: max_info)
    for (i = 0 ; i < vcount ; i++) {
        double result = get_l(i);
        struct Compare new_compare;
        new_compare.l_value = result;
        new_compare.vid = i;
        max_info = new_compare;
/*
#       pragma omp critical
        {
        if (result > max_info.l_value) {
            max_info.l_value = result;
            max_info.vid = i;
        }
        }
*/
    }
    STOP_TIMER(max_count)
    
    printf("max_vertex: %d\tmax_l: %f\n", max_info.vid, max_info.l_value);
    printf("Find Max Time: %f\n", GET_TIMER(max_count));
    igraph_destroy(&graph);
    return 0;
}

/**
 * Gets the l_value for the passed vertex by getting its neighbors and calculating its degree
 * along with a summation of the w_value for each edge from its self to one of its neighbors
 */
double get_l(int vid) {
    int i;
    double l_value;
    igraph_vs_t current = igraph_vss_1(vid);
    igraph_vector_t neighbors;
    int vector_size;
    double w_sum;

    igraph_vector_init(&neighbors, 0);

    // Get neighbors of vertex vid
    igraph_neighbors(&graph, &neighbors, vid, IGRAPH_ALL);
    
    vector_size = igraph_vector_size(&neighbors);
    
    //printf("Vector size: %d\n", vector_size);

//#   pragma omp parallel for default(none) shared(vector_size, neighbors, vid, current) \
    private(i) reduction(+ : w_sum)
    for (i = 0 ; i < vector_size ; i++) {

        int this_neighbor = (int) VECTOR(neighbors)[i];
        
        struct edge current = build_edge(vid, this_neighbor);

        w_sum += get_w(&current);
    }
    
    l_value = get_vertex_degree(vid) + w_sum;
    
    igraph_vector_destroy(&neighbors);
    igraph_vs_destroy(&current);

    return l_value;
}

/**
 * Gets the importance of the edge passed by dividing the u_value by the lambda value
 */
double get_importance(struct edge *current) {
    double u_value = get_u(current);
    double lambda = get_lambda(P_VALUE);

    return u_value / lambda;
}

/*
 * Gets the importance for the passed edge and multiplies it by
 * from_vertex_degree - 1 / from_vertex_degree + to_vertex_degree - 2.
 */
double get_w(struct edge *current) {
    double w_value;
    double importance = get_importance(current);

    w_value = importance * 
        ((current->from_degree - 1) / 
        (current->from_degree + current->to_degree - 2));

    return w_value;
}

/**
 * Sets the from and to vertex degrees and uses the degrees to calculate u.
 * (from_vertex_degree - P_VALUE - 1) * to_vertex_degree - P_VALUE - 1)
 */
double get_u(struct edge *current) {
    double u_value;

    current->from_degree = get_vertex_degree(current->from);
    current->to_degree = get_vertex_degree(current->to);
   
    u_value = (current->from_degree - P_VALUE - 1) * (current->to_degree - P_VALUE - 1);
    

    return u_value;
}

/**
 * Gets the lambda value by dividing the passed p_value by 2 and adding 1.
 */
double get_lambda(int p_value) {
    return (p_value / 2.0) + 1;
}

/**
 * Gets the degree of the passed vertex
 */
double get_vertex_degree(int vid) {
    igraph_vector_t degree;
    int result;
    igraph_vs_t vs = igraph_vss_1(vid);
    
    igraph_vector_init(&degree, 1);

    igraph_degree(&graph, &degree, vs, IGRAPH_ALL, true);

    result = VECTOR(degree)[0];

    igraph_vector_destroy(&degree);

    return result;
}

/**
 * Returns an edge struct given a from and to vertex id
 */
struct edge build_edge(int from, int to) {
    struct edge new_edge;
    
    new_edge.from = from;
    new_edge.to = to;

    return new_edge;
}
