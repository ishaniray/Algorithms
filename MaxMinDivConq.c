/* This program finds the maximum and minimum values in a list of integers by adopting the divide-and-conquer approach */

#include <stdio.h>
#include <stdlib.h>

int maximum(int*, int, int);
int minimum(int*, int, int);

int maxcomp = 0, mincomp = 0;

int main(void)
{
	int *a, n, i, max, min;

	printf("How many numbers?\n");
	scanf("%d", &n);
	a = malloc(n * sizeof(int));

	printf("\n\nEnter numbers:\n");
	for(i = 0; i < n; ++i)
		scanf("%d", &a[i]);

	max = maximum(a, 0, n - 1);
	min = minimum(a, 0, n - 1);

	printf("\n\nThe maximum of the numbers entered is: %d", max);
	printf("\nThe miniimum of the numbers entered is: %d", min);

	printf("\n\nNo. of comparisons made while deducing the maximum number: %d", maxcomp);
	printf("\nNo. of comparisons made while deducing the minimum number: %d\n", mincomp);

	return 0;
}

int maximum(int *a, int low, int high)
{
	int mid, x, y;
	
	if(low < high)	/* if the current (sub)array has more than one element */
	{
		++maxcomp;
		mid = low + (high - low) / 2;
		x = maximum(a, low, mid);	/* maximum of left sub-tree */
		y = maximum(a, mid + 1, high);	/* maximum of right sub-tree */
		if(x > y)
			return x;
		else
			return y;
	}

	else
		return a[low];
}

int minimum(int *a, int low, int high)
{
	int mid, x, y;
	
	if(low < high)	/* if the current (sub)array has more than one element */
	{
		++mincomp;
		mid = low + (high - low) / 2;
		x = minimum(a, low, mid);	/* minimum of left sub-tree */
		y = minimum(a, mid + 1, high);	/* minimum of right sub-tree */
		if(x < y)
			return x;
		else
			return y;
	}

	else
		return a[low];
}
	
