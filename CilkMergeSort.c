#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cilk.h>
#include <time.h>

void create_array(int * x, int n) {
   int i,j,t;
   for (i = 0; i < n; i++)
     x[i] = i;
   for (i = 0; i < n; i++) {
     j = rand() % n;
     t = x[i];
     x[i] = x[j];
     x[j] = t;
   }
}

void print_list(int * x, int n) {
   int i;
   for (i = 0; i < n; i++) {
      printf("%d ",x[i]);
   }
}


void merge(int * X, int n, int * temp) {
   int i = 0;
   int j = n/2;
   int ti = 0;

   while (i<n/2 && j<n) {
      if (X[i] < X[j]) {
         temp[ti] = X[i];
         ti++; i++;
      } else {
         temp[ti] = X[j];
         ti++;
         j++;
      }
   }
   while (i<n/2) { 
      temp[ti] = X[i];
        ti++;
        i++;
   }
      while (j<n) { 
         temp[ti] = X[j];
         ti++;
         j++;
   }
        
   memcpy(X, temp, n*sizeof(int));
} 

void mergesort(int * X, int n, int * temp)
{
   if (n < 2) return;

   cilk_spawn mergesort(X, n/2, temp);

   cilk_spawn mergesort(X+(n/2), n-(n/2), temp);

   cilk_sync;

   merge(X, n, temp);
}

int cilk_main()
{
   int n = 32;
   double start_time, end_time,val;
   int temp[32];
   int array[] = {9, 5, 1, 5, 19, 32, 48, 55, 66, 159, 957, 326, 15, 0, 51, 5, 3, 222, 213, 357, 68, 45, 21, 23, 32, 45, 7, 8, 32, 100, 101, 10};
   printf("The list before sorting:\n");
   print_list(array, n);
   start_time = clock();
   mergesort(array, n, temp);
   end_time = clock();  
   printf("\nOriginal List (32 Elements):\n");
   print_list(array, n);
	val=(end_time-start_time);
   printf("\nThe time taken to sort the array elements is: %f\n",val);
}