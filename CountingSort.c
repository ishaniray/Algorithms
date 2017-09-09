#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void countingSort(int*, int*, int, int);

int main(void)
{
	int n, *a, *b, i, k;
	clock_t timer;
	double time_taken;

	printf("How many numbers do you wish to sort?\n");
	scanf("%u", &n);

	a = malloc((n + 1) * sizeof(int)); /* Creating space for input array */
	b = malloc((n + 1) * sizeof(int));	/* Creating space for sorted array */

	printf("\n\nEnter %u numbers (>= 0):\n", n);
	for(i = 1; i < (n + 1); ++i)
		scanf("%u", &a[i]);

	/* Finding out the maximum element of the input array and storing it in 'k' */
	k = a[1];
	for(i = 2; i < (n + 1); ++i)
		if(a[i] > k)
			k = a[i];

	timer = clock(); /* Setting the timer */
	countingSort(a, b, n, k); /* Applying the Counting Sort algorithm */
	timer = clock() - timer;
	time_taken = (double)timer / CLOCKS_PER_SEC;

	/* Printing the results */
	printf("\n\nThe list you entered: ");
	for(i = 1; i < (n + 1); ++i)
		printf("%u ", a[i]);
	printf("\nSorted list: ");
	for(i = 1; i < (n + 1); ++i)
		printf("%u ", b[i]);
	printf("\nSorting completed in: %f seconds.\n", time_taken);


	return 0;
}

void countingSort(int *a, int *b, int n, int k)
{
	int i, *c;
	c = malloc((k + 1) * sizeof(int)); /* Creating space for auxilliary array */

	/* Initializing aux. array */
	for(i = 0; i < k; ++i)
		c[i] = 0;

	/* Updating the frequency of elements occuring in a[] */
	for(i = 1; i < (n + 1); ++i)
		++c[a[i]];

	/* Updating the frequencies with cumulative frequencies */
	for(i = 1; i < (k + 1); ++i)
		c[i] = c[i] + c[i - 1];

	/* Traversing a[] from the end and putting each element in its proper position in b[] */
	for(i = n; i > 0; --i)
	{
		b[c[a[i]]] = a[i];
		--c[a[i]];
	}
}

