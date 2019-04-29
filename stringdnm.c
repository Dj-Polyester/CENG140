#include <stdio.h>
#include <stdlib.h>

int lenstr(char* str)
{
	int i=0;
	while(str[i])
	{
		++i;
	}
	return i;
}

char* vacuum(char* str)
{
	char current,*strvac;
	int i=0;
	
	while(current=str[i])
	{
		printf("%c",current);
		if(current!=' ')
		{
			++i;
		}	
	}
	printf("%d",i);
	strvac=malloc(i+1);
	i=0;
	while(current=str[i])
	{
		if(current!=' ')
		{
			printf("%c",current);
			strvac[i]=str[i];
			++i;
		}	
	}
	strvac[i]=0;
	return strvac;
}
/*
char* pile(char* str1,char* str2)
{
	int len1=lenstr(str1),len2=lenstr(str2),maxlen,minlen,length=len1+len2,i=0,j=0,k=0;
	char* str;
	
	
	if(len1<len2)
	{
		maxlen=len2;
		minlen=len1;
	}
	if(len1>len2)
	{
		maxlen=len1;
		minlen=len2;
	}
	
	str=malloc(length+1);
	
	while(str1[i] && str2[j])
	{
		if(str1[i]==' ')
		{
			++i;
			continue;
		}
		if(str2[j]==' ')
		{
			++j;
			continue;
		}
		
		str[k]=str1[i];
		str[k+1]=str2[j];
		
		k+=2;
		++j;
		++i;
		
	}
	
	str[length-1]=0;
	
	return str;
}

*/
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

int main()
{
	char *str1=0,*str2=0;
	char *str=0;
	
	str1=getIn();
	str2=getIn();
	
	//str=pile(str1,str2);
	
	str1=vacuum(str1);
	str2=vacuum(str2);
	
	printf("%s",str1);
	printf("%s",str2);
	
	if(str1) free(str1);
	if(str2) free(str2);
	if(str ) free(str);
	return 0;
}
