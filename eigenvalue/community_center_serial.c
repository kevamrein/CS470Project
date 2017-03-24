#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <igraph.h>

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
void printMatrix()
{
	long row, col;

	for (row = 0; row <nodes_num; row++)
	{
		for (col=0; col<nodes_num;col++)
		{
			printf("%1.0lf ", igraph_matrix_e(&adjMatrix, row, col));
		}
		printf("\n");

	}
}

int findCentrality()
{
	/*int igraph_lapack_dgeev(const igraph_matrix_t *A, 
						igraph_vector_t *valuesreal,
						igraph_vector_t *valuesimag, 
						igraph_matrix_t *vectorsleft,
						igraph_matrix_t *vectorsright, 
						int *info);*/

	int eigenV = 0;
	int info = 1;
	eigenV = igraph_lapack_dgeev(&adjMatrix, NULL, NULL, NULL, NULL, &info);
	return eigenV;
}

int main(int argc, char *argv[]) {
	char* filename;
	// read in filename from command line first
    filename="community.txt";
	
	if (argc ==2)
		filename = argv[1];

	createMatrix(filename);	
	printMatrix();
	printf("Eigenvalue is: %d\n", findCentrality());	

 	igraph_matrix_destroy(&adjMatrix);

	return 0;
}
