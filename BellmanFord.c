/* Bellman-Ford algorithm: Finding the single-source shortest path from Vertex 1 to all other vertices in a weighted, directed graph.
   (For the purpose of this program, INT_MAX is assumed to denote infinity.) */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0

/* Function prototypes */
int* bellmanFord(int**, int, int, int*);
void relax(int**, int, int*, int*);

int main(void)
{
	int **cost, v, i, j, *path, numofedges = 0, negativeCycle = FALSE;
	char x, y;

	printf("How many vertices does your graph have?\n");
	scanf("%d", &v);

	/* Creating space for a 'v' by 'v' cost-matrix */
	cost = malloc(v * sizeof(int*));
	for(i = 0; i < v; ++i)
		cost[i] = malloc(v * sizeof(int));

	/* Initializing all values of 'cost' matrix to infinity */
	for(i = 0; i < v; ++i)
		for(j = 0; j < v; ++j)
			cost[i][j] = INT_MAX;

	printf("\n\nPlease enter the cost matrix for the directed graph (vertex numbering starts from 1):");
	printf("\n[Keep entering (i, j) pairs; hit 'E' (or 'e') to break out.]");
	do
	{
		printf("\n\nEnter i: ");
		scanf(" %c", &x);

		if(x == 'E' || x == 'e')
			break;

		i = x - '0' - 1;	/* converting char digit to int (offset value) */

		printf("\nEnter j: ");
		scanf(" %c", &y);	/* converting char digit to int (offset value) */

		j = y - '0' - 1;

		printf("\nEnter weight: ");
		scanf("%d", &cost[i][j]);

		++numofedges; /* incrementing edge-count */

	} while(TRUE);

	for(i = 0; i < v; ++i)
		cost[i][i] = INT_MAX;	/* Diagonal elements must not have a value other than infinity */

	path = bellmanFord(cost, v, numofedges, &negativeCycle);

	if(!negativeCycle)
	{ 
		for(j = 1; j < v; ++j)
		{
			printf("\n\nThe shortest path from %d to %d is: ", 1, j + 1);
			for(i = 0; i < v; ++i)
			{
				if(path[i] != j + 1)
					printf("%d -> ", path[i]);
				else
				{
					printf("%d\n", path[i]);
					break;
				}
			}
		}
	}
	else
		printf("\n\nA negative cycle exists in the graph!\n");

	return 0;
}

/*	Function implementing Bellman-Ford algorithm.
	Array indices serve as vertex numbers */
int* bellmanFord(int** cost, int v, int numofedges, int* negativeCycle)
{
	int *distance, **edge, *predecessor, i, j, k, *path, current;

	/* Creating space for 'path' vector, which would store the shortest path from the source vertex to all other vertices */ 
	path = malloc(v * sizeof(int));
	
	/* Creating space for 'distance' vector, which would store the distance from the source vertex to each of the other vertices */
	distance = malloc(v * sizeof(int));
	
	/* Initializing distance vector */
	distance[0] = 0;				/* distance from Source to itself is zero */
	for(i = 1; i < v; ++i)			/* for all other vertices... */
		distance[i] = INT_MAX;		/* ...distance is initialized to infinity. */

	/*Creating space for 'edge' matrix, which is a 'numofvertices' by 3 matrix, storing - for each edge - the two endpoints and the distance from one endpoint to the other */
	edge = malloc(numofedges * sizeof(int*));
	for(i = 0; i < numofedges; ++i)
		edge[i] = malloc(3 * sizeof(int));

	/* Populating 'edge' matrix by traversing 'cost' matrix */
	k = 0;
	for(i = 0; i < v; ++i)
	{
		for(j = 0; j < v; ++j)
		{
			if(cost[i][j] != INT_MAX) 		/* if there is an edge... */
			{
				edge[k][0] = i; 			/* ...first column stores Vertex 'i'... */
				edge[k][1] = j;				/* ...second column stores Vertex 'j'... */
				edge[k][2] = cost[i][j];	/* ...third column stores the distance from Vertex 'i' to Vertex 'j'. */
				++k;						/* incrementing rowcount */
			}
		}
	}

	/* Creating space for 'predecessor' array, which would store the predecessor for each vertex in the shortest path */
	predecessor = malloc(v * sizeof(int));

	/* Initializing 'predecessor' array to infinity, for all vertices */
	for(i = 0; i < v; ++i)
		predecessor[i] = INT_MAX;

	/* Bellman-Ford algo.: */
	for(i = 0; i < v - 1; ++i)						/* for each vertex other than the starting one */
		for(j = 0; j < numofedges; ++j)				/* for each edge */
			relax(edge, j, distance, predecessor);	/* perform 'relax' operations */

	/* Execute another pass. If values still change, a negative cycle exists. */
	for(i = 0; i < numofedges; ++i)
	{
		if(distance[edge[i][1]] > distance[edge[i][0]] + edge[i][2])
		{
			*negativeCycle = TRUE;
			break;
		}
	}

	/* Building the path.
	   Idea: For each vertex added to the path, we will see which vertex it is the predecessor to, 
			 and that would be the next vertex to be added to the path */

	path[0] = 0 + 1;	/* The first vertex in the path is the source vertex (1 is added since vertex numbering starts from 1) */
	current = 0;		/* 'current' keeps track of the most recent vertex added to the path  */

	for(k = 1; k < v; ++k)		/* for each of the spaces left in the path (1st index to 'v - 1'th index) */
	{
		for(i = 1; i < v; ++i)	/* traverse 'predecessor' array, ignoring the 0th index since the source vertex does not have any predecessor */
		{
			if(predecessor[i] == current)	/* if the successor of the 'current' vertex is found... */
			{
				path[k] = i + 1;			/* ...add it to path (add 1, since vertex numbering starts from 1)... */
				current = i;				/* ...change 'current' to ith vertex... */
				break;						/* ...move on to the next iteration. */
			}
		}
	}

	return path;				
}

/* Function definition for relax() */
void relax(int** edge, int j, int* distance, int* predecessor)
{
	if(distance[edge[j][1]] > distance[edge[j][0]] + edge[j][2]) /* if distance from Source to Vertex B is greater than distance from Source to Vertex A + distance from Vertex A to Vertex B */
	{
		/* update values */
		distance[edge[j][1]] = distance[edge[j][0]] + edge[j][2];
		predecessor[edge[j][1]] = edge[j][0];
	}
} 
