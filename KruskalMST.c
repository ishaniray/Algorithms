/* Program to find the minimum spanning tree of a weighted, undirected graph, implementing Kruskal's algorithm. */

   #include <stdio.h>
   #include <stdlib.h>

   /* Structure definition - 'u' and 'v' are two vertices of an edge; 'weight' denotes the cost of the edge */
   struct edge
   {
       int u;
       int v;
       int weight;
   };
   
   /* Function prototypes */
   int kruskal(int, int, struct edge*, int**);
   void quickSort(struct edge*, int, int);
   int partition(struct edge*, int, int);
   int set(int, int*);
   
   int main(void)
   {
       int i, j, k, n, **cost, **MST, minCost = 0, numofedges;
       struct edge *edgeSet;
   
       printf("How many vertices does your graph have?\n");
       scanf("%d", &n);

       printf("\n\nHow many edges does your graph have?\n");
       scanf("%d", &numofedges);
   
       /* Creating space for MST, which is a (n - 1) by 2 matrix holding the minimum spanning tree (the two columns hold the two vertices of an edge) */
       MST = malloc((n - 1) * sizeof(int*));
       for(i = 0; i < n - 1; ++i)
           MST[i] = malloc(2 * sizeof(int));

       /* Creating space for edgeSet, which is an array holding information ('u', 'v', 'weight') about each of the edges in the graph */
       edgeSet = malloc((numofedges) * sizeof(struct edge));
   
       printf("\n\nEnter edges and their weights (vertex numbering starts from zero):");
       for(k = 0; k < numofedges; ++k)
       {
           printf("\n\nEnter i: ");
           scanf("%d", &edgeSet[k].u);
   
           printf("\nEnter j: ");
           scanf("%d", &edgeSet[k].v);
   
           printf("\nEnter cost: ");
           scanf("%d", &edgeSet[k].weight);
       }
   
       minCost = kruskal(n, numofedges, edgeSet, MST);
       
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
   
   /* Function implementing Kruskal's algorithm.
      Array indices serve as vertex numbers.
      Idea: In the beginning, all vertices are separate sets.
            To find each of the n - 1 edges, the edge-set is first sorted in non-decreasing order of weight.
            The edge with the least cost is added to the MST, but only if the vertices of that edge belong to separate sets.
            (Joining vertices belonging to the same set would result in a cycle.)
            If the vertices of the least-cost edge belong to the same set, the next best option is considered, and so on.
            After adding an edge to the MST, set-union operations are performed on its vertices.
            The process continues until n - 1 edges have been found, and only one, cumulative vertex-set remains.
            (In this program, the concept of trees has been applied to represent sets.)  */
   int kruskal(int n, int numofedges, struct edge *edgeSet, int** MST)
   {
        int *parent, i, j, minCost = 0; 

        /* Creating space for 'parent' vector, which, for each of the vertices, keeps track of the set it belongs to by listing its parent in the tree */
        parent = malloc(n * sizeof(int));

        for(i = 0; i < n; ++i)
            parent[i] = -1;     /* since all vertices are separate sets (single-node trees) in the beginning, 'parent' array is initialized to an invalid value */

        for(i = 0; i < n - 1; ++i)  /* for each of the edges to be added to the MST */
        {
            quickSort(edgeSet, 0, numofedges - 1);  /* sort the edge-set in non-decreasing order of weight */

            j = 0;  /* initialize 'j' to denote first index in the sorted edge-set */
            while(set(edgeSet[j].u, parent) == set(edgeSet[j].v, parent))   /* while a least-cost edge with vertices belonging to different sets is not found... */
                ++j;                                                        /* ...increment 'j'. */

            /* Add the 'jth' edge to MST */
            MST[i][0] = edgeSet[j].u;
            MST[i][1] = edgeSet[j].v;
            MST[i][2] = edgeSet[j].weight;
            minCost = minCost + edgeSet[j].weight;

            /* Perform set-union operation by combining the trees of the two vertices - one vertex now becomes the child of another, thereby belonging to the same set */
            parent[edgeSet[j].v] = edgeSet[j].u;
        }

        return minCost;     /* return cost of MST */
   }

   /* Function definition for quickSort() */
   void quickSort(struct edge *edgeSet, int low, int high)
   {
        int pivotPos;
        if(high > low)
        {
            pivotPos = partition(edgeSet, low, high);
            quickSort(edgeSet, low, pivotPos - 1);
            quickSort(edgeSet, pivotPos + 1, high);
        }
   }

   /* Function definition for partition() */
   int partition(struct edge *edgeSet, int low, int high)
   {
       int i, lastSmall;
       struct edge pivot, temp;

       pivot = edgeSet[low];
       lastSmall = low;

       for(i = low + 1; i <= high; ++i)
       {
           if(edgeSet[i].weight < pivot.weight)
           {
               ++lastSmall;
               temp = edgeSet[lastSmall];
               edgeSet[lastSmall] = edgeSet[i];
               edgeSet[i] = temp;
           }
       }

       edgeSet[low] = edgeSet[lastSmall];
       edgeSet[lastSmall] = pivot;

       return lastSmall;
   }

   /* Function to return the set (Set No.) a vertex belongs to */
   int set(int vertex, int *parent)
   {
        int i = vertex;

        /* Find root node of set (tree) */
        while(parent[i] > -1)
            i = parent[i];

        return i;
   }
