/* Fractional Knapsack Problem (Greedy Algorithm) */

#include <stdio.h>
#include <stdlib.h>

/* structure definition */
struct item
{
	int serialNo;
	float profit;
	float volume;
	float pvr; 	/* profit-volume ratio */
	float frac; 	/* the fraction to be taken */
};

/* function prototypes */
void quickSort(struct item*, int, int);
int partition(struct item*, int, int);
void greedyKnapsack(struct item*, float, int);

int main(void)
{
	int n, i;
	float bag;
	struct item *inventory;

	printf("How many items are there?\n");
	scanf("%d", &n);
	inventory = malloc(n * sizeof(struct item));

	printf("\n\nEnter details of all items, one by one -");
	for(i = 0; i < n; ++i)
	{
		printf("\n\nSerial number of the item: ");
		scanf("%d", &inventory[i].serialNo);
		printf("\nProfit: ");
		scanf("%f", &inventory[i].profit);
		printf("\nVolume: ");
		scanf("%f", &inventory[i].volume);
		inventory[i].pvr = inventory[i].profit / inventory[i].volume;
	}

	printf("\nEnter the volume of the bag: ");
	scanf("%f", &bag);

	quickSort(inventory, 0, n - 1);		/* sort the inventory in non-increasing order of pvr */

	greedyKnapsack(inventory, bag, n);

	printf("\n\nSOLUTION:\n\n");
	printf("Serial No.\t\tFraction to be taken\n\n");
	for(i = 0; i < n; ++i)
	{
		printf("%d", inventory[i].serialNo);
		printf("\t\t\t\t");
		printf("%f", inventory[i].frac);
		printf("\n");
	}

	return 0;
}

/* Function definition of quickSort() */
void quickSort(struct item *inventory, int low, int high)
{
	int pivot;
	if(low < high)
	{
		pivot = partition(inventory, low, high);
		quickSort(inventory, low, pivot - 1);
		quickSort(inventory, pivot + 1, high);
	}
}

/* Function definition of partition() */
int partition(struct item *inventory, int low, int high)
{
	int lastBig, i;
	struct item pivot, temp;
	pivot = inventory[low];          /* The first element of the (sub)array is chosen to be the pivot */
	lastBig = low;
	for(i = low + 1; i <= high; ++i)
	{
		if(inventory[i].pvr > pivot.pvr)	/* sorting to be done on the basis of PVRs (non-increasing order) */
		{
			++lastBig;
			temp = inventory[lastBig];
			inventory[lastBig] = inventory[i];
			inventory[i] = temp;
		}
	}
	inventory[low] = inventory[lastBig];
	inventory[lastBig] = pivot;
	return lastBig;
}

/* Function definition of greedyKnapsack() */
void greedyKnapsack(struct item *inventory, float bag, int n)
{
	int i; 
	float RCB; /* RCB: Remaining Capacity of Bag */

	for(i = 0; i < n; ++i)
		inventory[i].frac = 0.0; 	/* initialising all values to 0.0 */

	RCB = bag;

	for(i = 0; i < n; ++i)
	{
		if(!RCB)	/* if capacity of the bag is exhausted... */
			break;	/* ...break out. */

		if(inventory[i].volume <= RCB)
			inventory[i].frac = 1.0;	/* take the whole item */
		else
			inventory[i].frac = RCB / inventory[i].volume;	/* take a fraction of the item */

		RCB -= (inventory[i].frac) * (inventory[i].volume);	/* reduce RCB's capacity by the the quantity taken */
	}
}
