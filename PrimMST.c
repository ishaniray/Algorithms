/* Program to find the minimum spanning tree of a weighted, undirected graph, implementing Prim's algorithm. 
   (For the purpose of this program, INT_MAX is assumed to denote infinity.) */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Function prototype */
int prim(int**, int, int**);

int main(void)
{
	int i, j, n, **cost, **MST;
	int minCost = 0;
	char x, y;

	printf("How many vertices does your graph have?\n");
	scanf("%d", &n);

	/* Creating space for cost-adjacency matrix */
	cost = malloc(n * sizeof(int*));
	for(i = 0; i < n; ++i)
		cost[i] = malloc(n * sizeof(int));

	/* Creating space for MST, which is a (n - 1) by 2 matrix holding the minimum spanning tree (the two columns hold the two vertices of an edge) */
	MST = malloc((n - 1) * sizeof(int*));
	for(i = 0; i < n - 1; ++i)
		MST[i] = malloc(2 * sizeof(int));

	/* Initializing values of cost-adjacency matrix to infinity */
	for(i = 0; i < n; ++i)
		for(j = 0; j < n; ++j)
			cost[i][j] = INT_MAX;

	printf("\n\nEnter edges and their weights (vertex numbering starts from zero):");
	printf("\n[Keep entering (i, j) pairs; hit 'E' (or 'e') to break out.]");
	do
	{
		printf("\n\nEnter i: ");
		scanf(" %c", &x);

		if(x == 'E' || x == 'e')
			break;

		i = x - '0';		/* converting char digit to int (offset value) */

		printf("\nEnter j: ");
		scanf(" %c", &y);	/* converting char digit to int (offset value) */

		j = y - '0';

		printf("\nEnter cost: ");
		scanf("%d", &cost[i][j]);
	
		cost[j][i] = cost[i][j];	/* since the graph is undirected, this statement holds true */

	} while(1);

	for(i = 0; i < n; ++i)
		cost[i][i] = INT_MAX; 		/* diagonal elements must have a cost of infinity */

	minCost = prim(cost, n, MST);
	
	printf("\n\nMST:\n");
	for(i = 0; i < n - 1; ++i)
	{
		for(j = 0; j < 2; ++j)
			printf("%d ", MST[i][j]);
		printf("\n");
	}

	printf("\nCost of the MST = %d\n", minCost);
	
	return 0;
}

/* Function implementing Prim's algorithm.
   Array indices serve as vertex numbers */
int prim(int** cost, int n, int** MST)
{
	int i, j, k, v, *near, minimum, minCost = 0;

	/* Creating space for 'near' array, which, for each vertex, stores a vertex from the under-construct MST nearest to it  */
	near = malloc(n * sizeof(int));

	near[0] = -1; /* Vertex 0 is initially in tree (once a vertex is in the MST, its 'near' value is changed to -1 (an invalid value)) */
	/* Initializing 'near' for all other vertices to 0, since Vertex 0 is the only vertex in the MST at the moment */
	for(i = 1; i < n; ++i)
		near[i] = 0;

	/* Prim's Algo.: */
	for(i = 0; i < n - 1; ++i)	/* for each edge to be added to the MST */
	{
		minimum = INT_MAX; 	/* initializing 'minimum' to infinity */

		/* Finding the least-cost vertex - a vertex whose addition to the tree would incur the least cost */
		for(j = 0; j < n; ++j)					/* for each vertex... */
		{
			if(near[j] != -1)				/* ...if the vertex hasn't already been added to the tree... */
			{
				if(cost[j][near[j]] < minimum)		/* ...if the distance between the current vertex and the vertex closest to it in the MST is lesser than the current minimum... */
				{
					minimum = cost[j][near[j]];	/* ...update 'minimum'... */
					v = j;				/* ...mark the current vertex for addition to the tree. */
				}
			}
		}
		j = v;	/* assign the final value of 'v' to 'j' */

		/* 'near[j]' and 'j' are the two vertices of the edge to be added to the MST */
		MST[i][0] = near[j];
		MST[i][1] = j;

		minCost = minCost + cost[j][near[j]];	/* cost of the edge between 'j' and 'near[j]' is added to the cost of the MST */
		near[j] = -1;				/* 'near' value of Vertex 'j' is updated to -1 since it is now in the MST */

		/* Updating 'near' values */
		for(k = 0; k < n; ++k)
		{
			if(near[k] != - 1)				/* if Vertex 'k' is yet to be added to MST... */
			{
				if(cost[k][j] < cost[k][near[k]])	/* ...if the distance between Vertex 'k' and the new vertex added to the tree ('j') is lesser than the distance between 'k' and 'near[k]'... */
					near[k] = j;			/* ...then, among vertices already in the MST, 'j' is now the vertex closest to 'k'. */
			}
		}
	}

	return minCost;		/* return the cost of the MST */
}
