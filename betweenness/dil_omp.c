#include <stdbool.h>
#include "graph.h"


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


int main(int argc, char* argv[]) {
    // Create graph
    graph = create_graph(argv[1]);
    
    int ecount = igraph_ecount(&graph);
    int vcount = igraph_vcount(&graph);
    struct edge *edges = get_edges(graph); 
    int i;
/*
    for (i = 0 ; i < ecount ; i++) {
        struct edge current = edges[i];
        
        double importance = get_importance(current);
        
        double w_value = get_w(current, importance);

        printf("%d -> %d \t importance: %f \t w: %f\n", current.from, current.to, importance, w_value);
        //printf("i: %d\t from: %d\t to: %d\n", i, current.from, current.to);
    }
*/

    for (i = 0 ; i < vcount ; i++) {
        printf("vertex: %d\n", i);
        double result = get_l(i);
        printf("L-Value: %f\n", result);
    }

    igraph_destroy(&graph);
    return 0;
}

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


double get_importance(struct edge *current) {
    double u_value = get_u(current);
    double lambda = get_lambda(P_VALUE);
//    printf("From: %d\tTo: %d\tFrom Degree: %f\tTo Degree: %f\n", current->from, current->to, current->from_degree, current->to_degree);
//    printf("U: %f\tLambda: %f\tImportance: %f\t", u_value, lambda, u_value / lambda);

    return u_value / lambda;
}

double get_w(struct edge *current) {
    double w_value;
    double importance = get_importance(current);

    w_value = importance * 
        ((current->from_degree - 1) / (current->from_degree + current->to_degree - 2));

//    printf("W: %f\n", w_value);


    return w_value;
}

double get_u(struct edge *current) {
    double u_value;

    current->from_degree = get_vertex_degree(current->from);
    current->to_degree = get_vertex_degree(current->to);
   
//    printf("From degree: %f to_degree: %f\n", current.from_degree, current.to_degree);
//    printf("FOMMM:%d TOOOO: %d", current.from, current.to);
    u_value = (current->from_degree - P_VALUE - 1) * (current->to_degree - P_VALUE - 1);
    

    return u_value;
}

double get_lambda(int p_value) {
    return (p_value / 2.0) + 1;
}

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

struct edge build_edge(int from, int to) {
    struct edge new_edge;
    
    new_edge.from = from;
    new_edge.to = to;

    return new_edge;
}
