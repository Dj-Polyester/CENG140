#include <stdio.h>
#include <math.h>
#include "usefulfunc.h"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#define PI 3.1415926535

int kbhit(void)
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
 
int main()
{
	int n;
  	char c;
	
	n=1;
	while(1)
	{
		printf("%d) %lf\n",n,n*sin(PI/n));
		sleep(0.5);
		if (kbhit())
		{	
			c=getchar();
			if (c==10)
			{
				printf("paused...\n");
				c=getchar();
				if(c==27) break;
	
			}
			else if (c==27) break;
		}
		n++;
	}
	
	
	return 0;
}
