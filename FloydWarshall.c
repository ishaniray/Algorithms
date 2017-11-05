/* Floyd-Warshall algorithm: Finding all pairs of shortest paths in a weighted digraph. */

   #include <stdio.h>
   #include <stdlib.h>
   
   #define TRUE 1
   #define FALSE 0
   #define INFINITY 1000000000
   
   /* Function prototype */
   void floydWarshall(int**, int, int*);
   
   int main(void)
   {
       int **cost, v, i, j, negativeCycle = FALSE;
       char x, y;
   
       printf("How many vertices does your graph have?\n");
       scanf("%d", &v);
   
       /* Creating space for a 'v' by 'v' cost (distance) matrix */
       cost = malloc(v * sizeof(int*));
       for(i = 0; i < v; ++i)
           cost[i] = malloc(v * sizeof(int));
   
       /* Initializing all values of 'cost' matrix to infinity */
       for(i = 0; i < v; ++i)
           for(j = 0; j < v; ++j)
               cost[i][j] = INFINITY;
   
       printf("\n\nPlease enter the cost matrix for the directed graph (vertex numbering starts from 0):");
       printf("\n[Keep entering (i, j) pairs; hit 'E' (or 'e') to break out.]");
       do
       {
           printf("\n\nEnter i: ");
           scanf(" %c", &x);
   
           if(x == 'E' || x == 'e')
               break;
   
           i = x - '0';	        /* converting char digit to int (offset value) */
   
           printf("\nEnter j: ");
           scanf(" %c", &y);	
   
           j = y - '0';         /* converting char digit to int (offset value) */
   
           printf("\nEnter weight: ");
           scanf("%d", &cost[i][j]);
   
       } while(TRUE);
   
       for(i = 0; i < v; ++i)
           cost[i][i] = 0;	/* the linear distance from a vertex to itself is zero */
   
       floydWarshall(cost, v, &negativeCycle);
   
       if(!negativeCycle)
       { 
           printf("\n\nThe shortest-path matrix for all pairs of vertices is:\n\n");
           for(i = 0; i < v; ++i)
           {
               for(j = 0; j < v; ++j)
                    printf("%d ", cost[i][j]);
                printf("\n");
           }
       }
       else
           printf("\n\nA negative cycle exists in the graph!\n");
   
       return 0;
   }

   /* Function implementing Floyd-Warshall's algorithm */
   void floydWarshall(int **cost, int v, int *negativeCycle)
   {
       int i, j, k;

       for(k = 0; k < v; ++k)   /* for each of the vertices */
       {
           /* Traverse distance matrix */
           for(i = 0; i < v; ++i)
           {
               for(j = 0; j < v; ++j)
               {
                   if(cost[i][j] > cost[i][k] + cost[k][j])     /* if distance from 'i' to 'j' is greater than distance from 'i' to 'k' + distance from 'k' to 'j'... */
                        cost[i][j] = cost[i][k] + cost[k][j];   /* ...distance from 'i' to 'j' = distance from 'i' to 'k' + distance from 'k' to 'j'. */
               }
           }
       }

       /* Check for negative cycles */
       for(i = 0; i < v; ++i)
       {
           if(cost[i][i] < 0)               /* if the principal diagonal of the shortest-path matrix has a negative value... */
           {
               *negativeCycle = TRUE;       /* ...a negative cycle exists. */
               break;
           }
       }
   }
