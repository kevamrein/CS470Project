#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <igraph.h>

int* nodes;
long nodes_num;
igraph_matrix_t adjMatrix;

void createMatrix(char* filename)
{
	char* line;	
	FILE *fp;
	fp = fopen(filename, "r");
	
	if (fp == NULL)	{
		printf("Could not read in file");
		exit(EXIT_FAILURE);
	}

	char nodes_string[255];
	nodes_num = atoi(fgets(nodes_string, 255, fp));
	line = malloc(sizeof(char*) * (nodes_num * 2));	
	
	nodes = malloc(sizeof(int*) * (nodes_num * nodes_num));
	long row = 0;
	long  col = 0;
	igraph_real_t node; 
	//void igraph_matrix_set(igraph_matrix_t* m, long int row, long int col,
	//						 igraph_real_t value);
	while (fgets(line, 255, fp) != NULL)
	{
		for (col = 0; col < nodes_num; col++) {
			nodes[row+col] = atoi(&line[col]);
			node = atoi(&line[col]);
			igraph_matrix_set(&adjMatrix, row, col, );
		}
		row++;
	}

	if (igraph_matrix_init(&adjMatrix, nodes_num, nodes_num) == -1)
	{
		printf("Error creating adjacency matrix\n");
		exit(EXIT_FAILURE);
	}

}

void printMatrix(int* matrix, int size)
{
	int row, col;
	printf("[");
	for (row = 0; row < size; row++)
	{
		for (col = 0; col < size; col++)
		{
			printf("%d", matrix[row+col]);
		}
		printf("\n");
	}
	printf("]\n");
}

int main(int argc, char *argv[]) {
	char* filename;

	// read in filename from command line first
    filename ="community.txt";

	createMatrix(filename);	
	printMatrix(nodes, nodes_num);	

	igraph_matrix_destroy(&adjMatrix);

	return 0;
}
