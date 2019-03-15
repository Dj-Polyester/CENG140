#include <stdio.h>
#include <stdlib.h>
#include "usefulfunc.h"
#include <ncurses.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

int kbhit()
{
  struct termios oldt, newt;
  int ch;
  int oldf;
 
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
  ch = getchar();
 
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
 
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }
 
  return 0;
}

int kbwait(char k) 
{
    char c;
    
   initscr ();
  	noecho ();

    while (1)
    {
      c = getch ();
   
      if (c == k)
      {
        break;
      }
    }

 	echo ();
  	endwin ();
    return 0;
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

void invert_array(int* array,const int count)
{
    for(int i=0;i<count/2;i++) swap(&array[i],&array[count-1-i]);
}

void swap(int *a,int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}

char* getIn() 
{
    char *line = NULL, *tmp = NULL;
    size_t size = 0, index = 0;
    int ch = EOF;

    while (ch) {
        ch = getc(stdin);

        /* Check if we need to stop. */
        if (ch == EOF || ch == '\n')
            ch = 0;

        /* Check if we need to expand. */
        if (size <= index) {
            size += sizeof(char);
            tmp = realloc(line, size);
            if (!tmp) {
                free(line);
                line = NULL;
                break;
            }
            line = tmp;
        }

        /* Actually store the thing. */
        line[index++] = ch;
    }

    return line;
}

int len(char* array)
{
	int i=0;
	while (array[i]!='\0')
	{
		i++;
		
	}
	return i;
	
}
