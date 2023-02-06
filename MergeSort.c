#include<stdio.h>
#include<omp.h>
#include<time.h>
void merge(int array[],int low,int mid,int high)
{
  int temp[32];
  int i,j,k,m; 
  j=low;
  m=mid+1;
  for(i=low; j<=mid && m<=high ; i++)
  {
     if(array[j]<=array[m])
     {
         temp[i]=array[j];
         j++;
     }
     else
     {
         temp[i]=array[m];
         m++;
     }
  }
  if(j>mid)
  {
     for(k=m; k<=high; k++)
     {
         temp[i]=array[k];
         i++;
     }
  }
  else
  {
     for(k=j; k<=mid; k++)
     {
        temp[i]=array[k];
        i++;
     }
  }
  for(k=low; k<=high; k++)
     array[k]=temp[k];
}


void mergesort(int array[],int low,int high)
{
 int mid;
 if(low<high)
 {
   mid=(low+high)/2;

   #pragma omp parallel sections 
    {
      #pragma omp section
        {
          mergesort(array,low,mid);
        }
      
      #pragma omp section
        {
          mergesort(array,mid+1,high);
        }
    }
   merge(array,low,mid,high);
 }
}


int main()
{
 int array[32];
 int i,size;
	double start_time,end_time,val;
 printf("Enter total no. of elements:\n");
 scanf("%d",&size);
 printf("Enter %d elements:\n",size);
 for(i=0; i<size; i++)
 {
   scanf("%d",&array[i]);
 }
start_time=omp_get_wtime();
 mergesort(array,0,size-1);
end_time=omp_get_wtime();
val=(end_time-start_time);
printf("The time taken to sort the array elements is %f \n",val);
 printf("Sorted Elements as follows:\n");
 for(i=0; i<size; i++)
    printf("%d ",array[i]);
 printf("\n");
 return 0;
}
