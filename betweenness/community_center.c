#include <mpi.h>
#include <igraph.h>

// Global Variables
int my_rank;
int nprocs;
graph_t graph;
igraph_vs_t *vertices;
int verticies_per_node;
igraph_vs_t local_verticies;   // This is the recv_buf if I make the datatype
double *local_double_verticies; // Trying this as the recvbuf now

// Function prototypes
igraph_vit_t* get_interators();

int main(int argc, char *argv[]) {
    /* Initialization */
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    if (my_rank == 0) {
        // Get adjacency matrix or edges from the file and use Chuchi's functions
        // and put it in graph

        // EXAMPLE GRAPH
        igraph_small(&graph, 0, IGRAPH_UNDIRECTED, 0, 1, 1, 2, 1, 3, 2, 3, 2, 4, 4, 6, 5, 6, 5,
            7, 6, 8, 7, 10, 7, 8, 8, 10, 8, 9, 8, 11, -1);

            /* Vertex count must be divisible by nprocs (for now until they can be
            dynamically allocated) */
        if (igraph_vcount(&graph) % nprocs != 0) {
            // Finalize and Destroy
            igraph_destroy(&graph);
            MPI_Finalize();

            return 1;
        }
        
        // Send each vector data as a double array using a vector view
        for (int i = 0 ; i < nprocs ; i++) {
            double *data;
            igraph_vector_copy_to(&verticies[i], data);

            MPI_Send(data, verticies_per_node, MPI_DOUBLE, 
                local_double_verticies, 0, MPI_COMM_WORLD);
        }

        /*
        igraph_vit_t iterators[nprocs] = get_iterators();
        
        MPI_Scatter(iterators, nprocs, , 
            recv_buff, recv_count, recv_dtype, recv_count, recv_dtype, 
            root, comm);
        */
    }
    MPI_Barrier(MPI_COMM_WORLD);
    calculate_max_betweenness();

    MPI_Finalize();
    return 0;
}

igraph_vit_t* get_iterators() {
    igraph_integer_t vertices_count = igraph_vcount(&graph);
    verticies_per_node = verticies_count / nprocs;
    igraph_vit_t iterators[nprocs];
    int start, end;
    vertices = (igraph_vs_t*) malloc(sizeof(igraph_vs_t) * nprocs);
    start = 0;
    end = verticies_per_node;

    for (int i = 0 ; i < nprocs ; i++) {
        igraph_vs_seq(&vertices[i], start, end);
        start = end + 1;
        end = start + verticies_per_node;
    }

    return iterators;
}

void calculate_max_betweenness() {
    igraph_vector_t current_vector, result;
    igraph_vector_view(&current_vector, local_double_verticies, verticies_per_node);
    igraph_betweenness(&graph, &result, );
}

void destroy_verticies_iterators(igraph_vit_t* iterators) {
    int i;
    for (i = 0 ; i < nprocs ; i++) {
        igraph_vit_destroy(&iterators[i]);
        igraph_vs_destroy(&verticies[i]);
    }
    free(iterators);
    free(verticies);
}
