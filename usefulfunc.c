#include <stdio.h>


int min(int *array,int count)
{
    int min,index;
    for(int i=0;i<count;i++)
    {
        if (i==0 || array[i] < min)
        {
            index=i;
            min=array[i];
        }
    }
    return index;
}

int max(int *array,int count)
{
    int max,index;
    for(int i=0;i<count;i++)
    {
        if (i==0 || array[i] > max)
        {
            index=i;
            max=array[i];
        }
    }
    return index;
}

void invert_array(int* array,const int count)
{
    for(int i=0;i<count/2;i++) swap(&dizi[i],&dizi[count-1-i]);
}

void swap(int *a,int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}

