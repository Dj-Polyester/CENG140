#include <stdio.h>
#include <conio.h>


int keypress(); //while(keypress()) tapped enter, stops the cycle

int min(int *array,int count); // array min-max
int max(int *array,int count);


int main()
{
    while(keypress()) printf("a");

    getch();
}
int keypress()
{
    char c;
    if (kbhit())
    {
        c=getch();
        if ( c==13)
        {
            return 0;
        }
    }
    return 1;
}

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

void invert_array()
{
    const int count=obtaindata("a count");
    int *dizi=obtainarray(count);

    for(int i=0;i<count/2;i++) swap(&dizi[i],&dizi[count-1-i]);
    //pointerlar direk gönderilir, pointer olmayan & ile gönderilir (doğru mu?)
    prntarray(dizi,count);
    free(dizi);
}

void swap(int *a,int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}

