#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printMatrix(int* matrix, int size);

int main(int argc, char *argv[]) {
	printf("running\n");
	char* line;
	int nodes_num;
	char nodes_string[255];
	char* filename;
    filename ="community.txt";
	FILE *fp;
	fp = fopen(filename, "r");
	
	if (fp == NULL)	{
		printf("Could not read in file");
		exit(EXIT_FAILURE);
	}

	nodes_num = atoi(fgets(nodes_string, 255, fp));
 	printf("%d\n", nodes_num);
	line = malloc(sizeof(char*) * (nodes_num * 2));	
	
	int* nodes = malloc(sizeof(int*) * (nodes_num * nodes_num));
	int row = 0;
	int col = 0;
	while (fgets(line, 255, fp) != NULL)
	{
		for (col = 0; col < nodes_num; col++) {
			nodes[row+col] = atoi(&line[col]);
		}
		row++;
	}

	printMatrix(nodes, nodes_num);	

	return 0;
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
