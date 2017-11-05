/* Breadth-first traversal of an undirected, unweighted graph */

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

/* structure definition of a node in a linked-list */
struct qnode
{
	int number;
	struct qnode *next;
};

typedef struct qnode* QNODEPTR;

/* function prototypes */
int* traversal(int**, int*, int, int);
void enqueue(int);
int dequeue();

/* Declaring and initialising the external pointer to a queue of vertices (implemented via a linked-list) */
QNODEPTR list = NULL;

int main(void)
{
	int v, i, j, **a, *path, *visited, start;
	char x, y;

	printf("How many vertices does your graph have?\n");
	scanf("%d", &v);

	/* Creating a 'visited' array and initialising all values to FALSE.
	   (visited[i] == FALSE indicates that the ith vertex has not yet been added to the path.) */
	visited = malloc(v * sizeof(int));
	for(i = 0; i < v; ++i)
		visited[i] = FALSE;

	/* Creating space for a v by v adjancency matrix and initialising all values to 0 */
	a = malloc(v * sizeof(int*));
	for(i = 0; i < v; ++i)
		a[i] = malloc(v * sizeof(int));

	for(i = 0; i < v; ++i)
		for(j = 0; j < v; ++j)
			a[i][j] = 0;

	printf("\n\nIn which positions does the adjancency matrix have a '1'?");
	printf("\n[Keep entering (i, j) pairs; hit 'E' (or 'e') to break out.]");
	do
	{
		printf("\n\nEnter i: ");
		scanf(" %c", &x);

		if(x == 'E' || x == 'e')
			break;

		i = x - '0' - 1;	/* converting char digit to int (offset value) */

		printf("\nEnter j: ");
		scanf(" %c", &y);	

		j = y - '0' - 1;	/* converting char digit to int (offset value) */

		a[i][j] = 1;

	} while(TRUE);

	printf("\n\nThe adjacency matrix you entered is:\n");
	for(i = 0; i < v; ++i)
	{
		for(j = 0; j < v; ++j)
			printf("%d ", a[i][j]);
		printf("\n");
	}

	printf("\n\nWhich vertex shall we start from?\n");
	scanf("%d", &start);

	path = traversal(a, visited, v, start - 1);

	printf("\n\nCorresponding path:\n");
	for(i = 0; i < v; ++i)
	{
		if(i != (v - 1))
			printf("%d -> ", (path[i] + 1));
		else
			printf("%d", (path[i] + 1));
	}

	printf("\n");
	
	return 0;
}

int* traversal(int** a, int* visited, int v, int start)
{
	int x, j, k = 0, *path;
	path = malloc(v * sizeof(int));		/* creating a 1-D matrix to store the path */
	enqueue(start);				/* enqueueing starting vertex */

	while(list)				/* while the queue isn't empty */
	{
		x = dequeue();				/* dequeueing a vertex */
		if(!visited[x])				/* if dequeued vertex has not yet been visited (i.e., added to the path)... */
		{			
			path[k++] = x;				/* ...adding it to the path... */
			visited[x] = TRUE;			/* ...and changing its status to indicate that it has been visited. */

			for(j = 0; j < v; ++j)
				if(a[x][j])			/* if dequeued vertex shares an edge with any other vertex... */
					enqueue(j);		/* ...enqueueing the latter. */
		}
	}

	return path;
}

/* Enqueue function of a circular queue implemented via a linked-list */
void enqueue(int num)
{
	QNODEPTR newNode = malloc(sizeof(struct qnode));
	newNode -> number = num;
	if(list == NULL)
		newNode -> next = newNode;
	else
	{
		newNode -> next = list -> next;
		list -> next = newNode;
	}
	list = newNode;
}

/* Dequeue function of a circular queue implemented via a linked-list */
int dequeue()
{
	int val;
	QNODEPTR delNode;
	delNode = list -> next;
	if(list == delNode)
		list = NULL;
	else
		list -> next = delNode -> next;
	val = delNode -> number;
	free(delNode);
	return val;
}

