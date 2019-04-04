#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include "usefulfunc.h"

void tick(int first, ...)
{
	int val=first,count=0,*tickarray,i,token;
	char c=0;
	va_list valist,vl_count;
	va_start(valist, first);
	
	/* count number of arguments: */
  	va_copy(vl_count,valist);
  	while (val != 0) 
  	{
  	  	val=va_arg(vl_count,int);
  	  	++count;
 	}
  	va_end(vl_count);
	
	tickarray=calloc(count,sizeof(int));

	while(1)
	{
		if(kbhit()) c=getchar();
		
		for(i=count-1;i>-1;--i) printf("%d ",tickarray[i]);
		printf("\n");
		
		++tickarray[0];
		va_copy(vl_count,valist);
		
		if(tickarray[0]==first)
		{
			tickarray[0]=0;
			++tickarray[1];
		}
		
		for(i=1;i<count;++i)
			{
				token=va_arg ( vl_count, int);
				
				if(tickarray[i]==token)
				{
					if(i==count-1)
					{
						tickarray=fullnull(tickarray,count);
						break;
					}
					else
					{
						tickarray[i]=0;
						++tickarray[i+1];
					}
				} 
			}
			
			
			va_end(vl_count);
			sleep(1);
			if(c==27) break;
		
	}
	va_end(valist);
	free(tickarray);
	
}

int main()
{
	tick(4,3,2,2,0); return 0;
}



