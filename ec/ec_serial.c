#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <igraph.h>

/** Uncomment this for debugging **/
//#define _debug

/**
 * This program is a serial implementations of linear algebra,
 * specifically eigenvalue estimations used
 * to determine the central node within a community
 * of connected nodes.
 *
 * It will only work for communities that have a single
 * central node. If there are nodes with equal centrality, 
 * the program will return the node with sequential
 * precedence.
 *
 * author: Samantha Carswell
 * version 04-12-2017
 */
long	 			nodes_num;
igraph_matrix_t		adjMatrix;

/**
 * Create adjacency matrix from specified file.
 */
void createMatrix(char* filename)
{
    char* 			line;	
    FILE 			*fp;
    char			nodes_string[255];
    long 			idx=0;
    long			curr=0;
    igraph_real_t	node;

    fp = fopen(filename, "r");

    if (fp == NULL)	{
        printf("Could not read in file");
        exit(EXIT_FAILURE);
    }

    nodes_num = atoi(fgets(nodes_string, 255, fp));
    line = malloc(sizeof(char*) * (nodes_num * 2));	

    if (igraph_matrix_init(&adjMatrix, nodes_num, nodes_num) == -1)
    {
        printf("Error creating adjacency matrix\n");
        exit(EXIT_FAILURE);
    }

    for (; idx<nodes_num; idx++)
    {
        for (curr=0; curr<nodes_num; curr++)
        {

            if (fscanf(fp, "%lf", &node) < 0)
            {
                printf("Error reading in file\n");
                exit(EXIT_FAILURE);
            }
            igraph_matrix_set(&adjMatrix, idx, curr, node);
        }
    }
}

/**
 * Print out current adjacency matrix.
 */
void printMatrix(igraph_matrix_t* matrix)
{
    long row, col, size;
    size = igraph_matrix_ncol(matrix);

    for (row = 0; row <size; row++)
    {
        for (col=0; col<size;col++)
        {
            printf("%1.0lf ", igraph_matrix_e(matrix, row, col));
        }
        printf("\n");

    }
}

/**
 * Returns the max eigenvalue from a vector
 * of eigenvalues.
 */
double max(igraph_vector_t *vector)
{
    int idx = 0;
    double value = 0;

    for (; idx<igraph_vector_size(vector); idx++)
    {
        if (value < igraph_vector_e(vector, idx))
            value = igraph_vector_e(vector, idx);
    }

    return value;

}

/**
 * Computes central node from an adjacency
 * matrix which represents a single community.
 * Implements eigenvalue calculations and methods
 * from ziGraph library to find the node which has
 * the most impact on the matrix upon its removal.
 *
 * Returns the central node.
 */
int findCentrality()
{
    igraph_vector_t		values;
    igraph_vector_t		col_values;
    igraph_vector_t 	row_values;
    igraph_matrix_t		A;
    double				init_eigenValue = 0.0;
    double 				curr_eigenValue = 0.0;
    double				max_eigenValue = 0.0;
    double				max_change = 0.0;
    double				curr_change = 0.0;
    double				i = 0;
    int					node = -1;
    int					info = 0;
    int					idx = 1;
    igraph_matrix_init(&A, nodes_num, nodes_num);
    igraph_vector_init(&values, 0);
    igraph_vector_init(&col_values, nodes_num);
    igraph_vector_init(&row_values, nodes_num);
    igraph_vector_fill(&col_values, 0);
    igraph_vector_fill(&row_values, 0);

    /*
     * Find initial eigenvalue of matrix.
     */
    igraph_lapack_dgeev(&adjMatrix, &values, NULL, NULL, NULL, &info);	
    init_eigenValue = max(&values);
#	ifdef _debug
    printf("Initial Eigenvalue: %lf\n", init_eigenValue);
#	endif
    for (idx=0; idx < nodes_num; idx++)
    {
        igraph_vector_fill(&values, 0);

        /* Copy contents of original matrix*/
        igraph_matrix_copy(&A, &adjMatrix);

        i = idx;
        /* Set row and col at current idx to all 0's */
        igraph_matrix_set_row(&A, &row_values, i);
        igraph_matrix_set_col(&A, &col_values, i);
#		ifdef _debug
        printf("\nAdjusted Matrix with idx=%d\n", idx);
        printMatrix(&A);
#		endif	
        /* Calculate eigenvalue on adjusted matrix*/
        igraph_lapack_dgeev(&A, &values, NULL, NULL, NULL, &info);
        curr_eigenValue = max(&values);
#		ifdef _debug
        printf("Matrix eigenvalue is: %lf\n", curr_eigenValue);
#		endif	
        /* Change in eigenvalue / initial eigenvalue */
        curr_change = (fabs(init_eigenValue - curr_eigenValue)) / init_eigenValue;	
#		ifdef _debug
        printf("%lf - %lf / %lf\n", init_eigenValue, curr_eigenValue, init_eigenValue);
        printf("Change in eigenvalue is %lf\n", curr_change);
#		endif
        //if (idx == 0 || idx == 33) 
        if (max_change < curr_change)
        {
            printf ("i: %d change: %f\n", idx, curr_change);	
            max_change = curr_change;
            max_eigenValue = curr_eigenValue;
            node = idx;
        }

    }


    igraph_vector_destroy(&values);
    return node;
}

/**
 * Takes in filename that contains adjacency
 * matrix and determines central node of that
 * matrix.
 */
int main(int argc, char *argv[]) {
    char* filename;
    // read in filename from command line first

    if (argc != 2)
    {
        printf("Please pass a  filename\n");
        exit(EXIT_FAILURE);
    }

    filename = argv[1];

    createMatrix(filename);	

    printf("Central node is: %d\n", findCentrality());

    printf("\n");
    igraph_matrix_destroy(&adjMatrix);

    return 0;
}
