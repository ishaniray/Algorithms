/* This program performs Merge Sort on a list of randomly generated integers and validates its best/average/worst-case time complexity [O(nlogn)] */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define CAPACITY 500
#define MAXVAL 10000

int comp = 0; /* Global variable to keep track of the number of comparisons made */

void mergeSort(int*, int, int, int*);
void merge(int*, int, int, int, int*);
void worstCaseArr(int*, int, int, int*);

int main(void)
{
	int num, i, j;
	int *a = malloc(sizeof(int) * CAPACITY);	/* Actual array */
	int *b = malloc(sizeof(int) * ceil(CAPACITY / 2)); /* Auxilliary array half the size of a[] */
	int *c = malloc(sizeof(int) * CAPACITY); /* Aux. array for copying purposes */

	clock_t timer;
	double time_taken;

	FILE *fp = fopen("Data.txt", "w");
	srand(time(NULL)); /* True randomization */

	/* Generating random numbers, copying them into an array, and writing them to a file */
	for(i = 0; i < CAPACITY; ++i)
	{
		num = rand() % MAXVAL + 1;
		a[i] = num;
		fprintf(fp, "%d ", num);
	}

	fclose(fp);

	/* Regular-case analysis */
	printf("REGULAR CASE:\n");
	timer = clock();
	mergeSort(a, 0, CAPACITY - 1, b);
	timer = clock() - timer;
	time_taken = (double)timer / CLOCKS_PER_SEC;
	printf("Sorting completed in: %f seconds.\n", time_taken);
	printf("No. of comparisons: %d.\n", comp);
	
	/* Writing the sorted result to another file */
	fp = fopen("SortedData.txt", "w");
	for(i = 0; i < CAPACITY; ++i)
		fprintf(fp, "%d ", a[i]);
	fclose(fp);

	/* Best-case analysis */
	printf("\nBEST CASE:\n");
	comp = 0;
	timer = clock();
	mergeSort(a, 0, CAPACITY - 1, b);
	timer = clock() - timer;
	time_taken = (double)timer / CLOCKS_PER_SEC;
	printf("Sorting completed in: %f seconds.\n", time_taken);
	printf("No. of comparisons: %d.\n", comp);

	worstCaseArr(a, 0, CAPACITY - 1, c); /* Converting sorted array a[] into an array which would result in the worst-case for Merge Sort */

	/* Worst-case analysis */
	printf("\nWORST CASE:\n");
	comp = 0;
	timer = clock();
	mergeSort(a, 0, CAPACITY - 1, b);
	timer = clock() - timer;
	time_taken = (double)timer / CLOCKS_PER_SEC;
	printf("Sorting completed in: %f seconds.\n", time_taken);
	printf("No. of comparisons: %d.\n", comp);

	return 0;
}

/* Function to recursively partition an array into sub-arrays and call the merge() function on them */
void mergeSort(int *a, int low, int high, int *b)
{
	int mid;
	if(low < high)	/* If the current array has more than 1 element */
	{
		mid = low + (high - low) / 2;
		mergeSort(a, low, mid, b);
		mergeSort(a, mid + 1, high, b);
		merge(a, low, mid, high, b);
	}
}

/* Function to combine two sorted sub-arrays - a[low...mid] and a[mid + 1...high] - into a single sorted array, a[low...high] */ 	
void merge(int *a, int low, int mid, int high, int *b)
{
	int i, j, k, blen;

	for(i = 0, j = low; j <= mid; ++i, ++j)
	{
		b[i] = a[j];	/* Copying the first sub-array into b[] */
	}

	blen = mid - low + 1; /* Computing the length of b[] */

	/* Comparing elements of the two sub-arrays and writing them into a[] accordingly */	
	for(i = 0, j = mid + 1, k = low; i < blen && j <= high; )
	{
		++comp;
		if(b[i] <= a[j])
			a[k++] = b[i++];
		else
			a[k++] = a[j++];
	}

	while(i < blen)	/* a[mid + 1...high] has been fully traversed and all its elements put in their proper places, but some elements of b[] are yet to be copied into a[] */
		a[k++] = b[i++];

	/* If 'i' runs its course first, the above need not be performed for the remaining elements of a[mid + 1...high] since they are already assuming their proper positions */

}

/* Function to convert a sorted array into an array which would result in the maximum number of comparisons while performing Merge Sort */
void worstCaseArr(int *a, int low, int high, int *c)
{
	int i, j, k, mid, clen;
	if(low < high)
	{
		for(i = 0, j = low; j <= high; ++i, ++j)
			c[i] = a[j]; /* Copying elements of a[] into c[] */

		clen = high - low + 1; /* Computing the length of c[] */

		mid = low + (high - low) / 2;

		/* Alternately distributing the sorted elements of c[] among a[low...mid] and a[mid + 1...high] */
		for(i = low, j = mid + 1, k = 0; k < clen; )
		{
			a[i++] = c[k++];
			if(k < clen)
				a[j++] = c[k++];
		}

		worstCaseArr(a, low, mid, c);
		worstCaseArr(a, mid + 1, high, c);
	}
}

