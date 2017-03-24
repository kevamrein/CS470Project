#include <stdbool.h>
#include "graph.h"


#define DEGREE_VECTOR_SIZE 2
#define P_VALUE 0
igraph_t graph;

// Function prototypes
double get_importance(struct edge current);
double get_u(struct edge current);
double get_lambda(int p_value);
void get_degree(struct edge current, igraph_vector_t *result);
double get_w(struct edge current, double importance);

int main(int argc, char* argv[]) {
    // Create graph
    graph = create_graph(argv[1]);
    
    int ecount = igraph_ecount(&graph);
    struct edge *edges = get_edges(graph); 
    int i;
    for (i = 0 ; i < ecount ; i++) {
        struct edge current = edges[i];
        
        double importance = get_importance(current);
        
        double w_value = get_w(current, importance);

        printf("%d -> %d \t importance: %f \t w: %f\n", current.from, current.to, importance, w_value);
        //printf("i: %d\t from: %d\t to: %d\n", i, current.from, current.to);
    }

    return 0;
}

double get_importance(struct edge current) {
    double u_value = get_u(current);
    double lambda = get_lambda(P_VALUE);

    return u_value / lambda;
}

double get_w(struct edge current, double importance) {
    double w_value;

    w_value = importance * 
        ((current.from_degree - 1) / (current.from_degree + current.to_degree - 2));

    return w_value;
}

double get_u(struct edge current) {
    igraph_vector_t result;
    double u_value;

    igraph_vector_init(&result, DEGREE_VECTOR_SIZE);
    
    get_degree(current, &result);
    
    current.from_degree = VECTOR(result)[0];
    current.to_degree = VECTOR(result)[1];

    u_value = (current.from_degree - P_VALUE - 1) * (current.to_degree - P_VALUE - 1);

    return u_value;
}

double get_lambda(int p_value) {
    return (p_value / 2.0) + 1;
}

void get_degree(struct edge current, igraph_vector_t *result) {
    igraph_vs_t vids;

    igraph_vs_seq(&vids, current.from, current.to);

    igraph_degree(&graph, result, vids, IGRAPH_ALL, true);
}
