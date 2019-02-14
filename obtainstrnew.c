#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void obtainstr(const char* str);
void free2darray(int* array, int membernum);
void createarraydnm();

int main()
{
    obtainstr("expression");
    //createarraydnm();
    //a_function();


    getch();
}

void createarraydnm()
{
    int*array=(int*)malloc(sizeof(int)*3);
    array[0]=1;
    array[1]=2;
    array[2]=3;
    for(int i=0; i<4; i++)
        printf("%d",array[i]);
    printf("\n");

    for(int j=4; j<8; j++)
        {
            int* array=(int*)realloc(array,sizeof(int)*j);
        }


    array[3]=4;
    array[4]=5;
    array[5]=6;
    array[6]=7;

    for(int i=0; i<7; i++)
        printf("%d",array[i]);
    free(array);
}


//obtainstr is the main function
void obtainstr(const char* str)
{
    char* dizi=(char*)malloc(sizeof(char));
    char c;
    int i=0;//the length of the array
    printf("Please enter a/an %s: ",str);
    while(1)
    {
        //when typed, get the input c
        c=getch();
        if(c==13) //if enter, new line
        {
            printf("\n");
            break;
        }
        else if(c==8) //if backspace, do what button normally does (overwrite the previous char)
        {
            printf("\b \b");
            i--;
        }
        else //write
        {
            putchar(c);
            i++;
            char* dizi=(char*)realloc(dizi,sizeof(char)*(i+1));
            dizi[i-1]=c;


        }
    }
    dizi[i]=0;

    //printf("%s",dizi);
    free2darray(dizi,i);
}

//this is freeing the allocated char array
void free2darray(int* array, int membernum)
{
    for(int i=0; i<membernum; i++)
    {
        free(array[i]);

    }
    free(array);
}

void a_function()
{
    int capacity = 10;
    int count = 40;
    int i;

    srand(time(NULL));

    int* array = (int*)malloc(capacity*sizeof(int));
    for (i=0; i<count; i++)
    {
        if (i==capacity)
        {
            capacity *= 2;
            array = (int*)realloc(array, capacity*sizeof(int));
        }
        int r=rand();
        array[i] = r%101;
    }
    for(i=0;i<count; i++) printf("%d\n",array[i]);
    free(array);
}
