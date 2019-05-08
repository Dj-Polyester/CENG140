#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usefulfunc.h"


void printchars(char* str)
{
	int i=0;
	while(str[i])
	{
		if(str[i]!=' ')printf("%c",str[i]);
		else printf("_");
		++i;
	}
	printf("\n");
}

char* vacuum(char* str)
{
	char *tmp,*vacuumed;
	int len_str=strlen(str),i=0,count=0;
	
	if(!(tmp=calloc(count+1,sizeof(char)))) return NULL;
	vacuumed=tmp;
	
	while(str[i])
	{
		if(str[i]!=' ')
		{
			vacuumed[count++]=str[i];
		}
		++i;
	}
	printchars(str);
	printf("%d",count);
	if(!count)
	{
		if(!(tmp=realloc(vacuumed,(count+1)*sizeof(char)))) return NULL;
		vacuumed=tmp;
		tmp=NULL;
	}
	printchars(str);
	return vacuumed;
}


char* piling(char* str1, char* str2)
{
	char* str1_cpy,*str2_cpy,*tmp,*piled;
	int len_str1=strlen(str1),len_str2=strlen(str2),len_piled=len_str1+len_str2,c1=0,c2=0,i=0;
	
	if(!(tmp=calloc(len_piled+1,sizeof(char)))) return NULL;
	piled=tmp;
	tmp=NULL;
	
	while(str1[c1] && str2[c2])
	{
		
		if(str1[c1]==' ')
		{
			++c1;
			continue;
		}
		if(str2[c2]==' ')
		{
			++c2;
			continue;
		}
		
		piled[i]=str1[c1];
		piled[i+1]=str2[c2];
		i+=2;
		++c1;
		++c2;
		
	}
	if(!str1[c1])
	{
		while(str2[c2])
		{
			piled[i++]=str2[c2++];
		}	
	}
	else if(!str2[c2])
	{
		while(str1[c1])
		{
			piled[i++]=str1[c1++];
		}	
	}
	
	return vacuum(piled);
}


int main()
{
	char *str1,*str2,*str3;
	
	str1=getIn();
	str2=getIn();
	
	printchars(str1);
	printchars(str2);
	
	str3=piling(str1,str2);
	
	printchars(str3);
	
	free(str1);
	free(str2);
	free(str3);

	return 0;
}


