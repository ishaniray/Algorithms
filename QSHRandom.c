/* Quick Sort - Hoare Partition:
   - Numbers are randomly generated
   - Pivot element is chosen at random */

   #include <stdio.h>
   #include <stdlib.h>
   #include <time.h>
   
   #define CAPACITY 10
   #define MAXVAL 100
   
   int count = 1;
   
   void quickSort(int*, int, int);
   int partition(int*, int, int);
   int randomNum(int, int);
   
   int main(void)
   {
       int i, *a, num;
       a = malloc(CAPACITY * sizeof(int));
   
       srand(time(NULL));
       for(i = 0; i < CAPACITY; ++i)
       {
           num = rand() % MAXVAL + 1;
           a[i] = num;
       }
   
       printf("a[]: ");
       for(i = 0; i < CAPACITY; ++i)
           printf("%d ", a[i]);
   
       quickSort(a, 0, CAPACITY - 1);
   
       printf("\n\nSorted a[]: ");
       for(i = 0; i < CAPACITY; ++i)
           printf("%d ", a[i]);
   
       printf("\n");
   
       return 0;
   }
   
   void quickSort(int* a, int low, int high)
   {
       int pivot, i;
       if(low < high)
       {
           pivot = partition(a, low, high);
   
           printf("\n\na[] after %dth pass: ", count);
           for(i = 0; i < CAPACITY; ++i)
               printf("%d ", a[i]);
           printf("\n(Pivot element: %d)", a[pivot]);
           ++count;
   
           quickSort(a, low, pivot - 1);
           quickSort(a, pivot + 1, high);
       }
   }
   
   /* Idea: Move i and j from opposite ends of the (sub)array if a[i] <= pivot and a[j] > pivot, respectively.
            If none of them can move in a particular iteration, exchange a[i] and a[j].
            Keep doing this until i crosses j.
            The last legitimate value of i, before it went on to cross j, is the pivot position. */
            
   int partition(int *a, int low, int high)
   {
       int i, j, flag, temp, pivot, randomPos;
       randomPos = randomNum(low, high);   /* a[randomPos] is our pivot */
       
       /* Bringing a[randomPos] to the front (swap with a[low]) */
       temp = a[low];
       a[low] = a[randomPos];
       a[randomPos] = temp;
       
       pivot = a[low];
   
       i = low + 1;
       j = high;
   
       while(i <= j)
       {
           flag = 0;
   
           if(a[i] <= pivot)
           {
               i++;
               flag = 1;
           }
   
           if(a[j] > pivot)
               --j;
           else
           {
               if(flag == 0)
               {
                   temp = a[i];
                   a[i] = a[j];
                   a[j] = temp;
               }
           }
       }
   
       a[low] = a[i - 1];
       a[i - 1] = pivot;
       return (i - 1);
   }
   
   /* Function to generate a random number between 'low' and 'high' */
int randomNum(int low, int high)
{
    int num;
    num = rand() % (high - low + 1);    /* generating a number from 0 to (high - low) */
    num += low;     /* adding the above (random offset) to low */
    return num;
}
