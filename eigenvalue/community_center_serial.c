#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <igraph.h>

// #define _debug

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

double max(igraph_vector_t *vector)
{
	int idx = 0;
	double value = 0;

	for (; idx<igraph_vector_size(vector); idx++)
	{
		printf("%lf, ", igraph_vector_e(vector, idx));
		if (value < igraph_vector_e(vector, idx))
			value = igraph_vector_e(vector, idx);
	}

	return value;

}

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
		printf("Matrix eigenvalue is: %lf\n", curr_eigenValue);
		/* Change in eigenvalue / initial eigenvalue */
		curr_change = (fabs(init_eigenValue - curr_eigenValue)) / init_eigenValue;	
#		ifdef _debug
		printf("%lf - %lf / %lf\n", init_eigenValue, curr_eigenValue, init_eigenValue);
		printf("Change in eigenvalue is %lf\n", curr_change);
#		endif
		if (max_change <= curr_change)
		{
			max_change = curr_change;
			max_eigenValue = curr_eigenValue;
			node = idx;
		}
	}

    igraph_vector_destroy(&values);
	return node;
}


int main(int argc, char *argv[]) {
	char* filename;
	// read in filename from command line first
    filename="community.txt";
	
	if (argc ==2)
		filename = argv[1];

	createMatrix(filename);	
#	ifdef _debug
	printMatrix(&adjMatrix);
#	endif

	//printCentralNodes(findCentrality());
 	printf("Central node is: %d\n", findCentrality());
	igraph_matrix_destroy(&adjMatrix);

	return 0;
}
