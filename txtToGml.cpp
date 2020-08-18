// converts a graph in a txt file into a gml graph

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 100

int main(int argc, char* argv[]){
	int n= 0, m= 0, x= 0, y= 0;
	char line[MAXLINE]; /* stores input line */
	bool* nodes;
	int* edges[2];
	int counter= 0;

	if(argc != 2){
		printf("\n usage: %s <input file>\n\n", argv[0]);
		exit(-1);
	}

	FILE* input = fopen(argv[1], "r");
	if(!input){
		fprintf(stderr, "Error opening file \"%s\".\n", argv[1]);
		exit(-1);
	}

	fgets(line, MAXLINE, input) != NULL;
	if(sscanf(line, "%d %d", &n, &m) != 2){
		fprintf(stderr, "Error reading graph size (%s).\n", argv[1]);
		exit(-1);
	}

	nodes= (bool*)malloc(n*sizeof(bool));
	for(int i= 0; i< n; i++) nodes[i]= false;

	edges[0]= (int*)malloc(m*sizeof(int));
	edges[1]= (int*)malloc(m*sizeof(int));
	for(int i= 0; i< m; i++){
		edges[0][i]= 0;
		edges[1][i]= 0;
	}

	while(fgets(line, MAXLINE, input) != NULL){
		switch(line[0]){
		case '\n':;
		case '\0': break;
		default:
			if(sscanf(line, "%d %d", &x, &y) != 2){
				fprintf(stderr, "Error reading graph size (%s).\n", argv[1]);
				exit(-1);
			}

			nodes[x-1]= true;
			nodes[y-1]= true;
			edges[0][counter]= x-1;
			edges[1][counter]= y-1;
			counter++;
		}
	}

	char filename[100];
	strcpy(filename, "input.gml");

	printf("output file created: %s\n\n", filename);
	FILE* output;
	output= fopen(filename, "w+");

	fprintf(output, "graph\n");
	fprintf(output, "[\n");
	fprintf(output, "\tdirected 0\n");

	for(int i= 0; i< n; i++)
		if(nodes[i]) fprintf(output, "\tnode\n\t[\n\t\tid %d\n\t]\n", i);

	for(int i= 0; i< m; i++) fprintf(output, "\tedge\n\t[\n\t\tsource %d\n\t\ttarget %d\n\t]\n", edges[0][i], edges[1][i]);
	fprintf(output, "]\n");
	fclose(input);
	fclose(output);
}




