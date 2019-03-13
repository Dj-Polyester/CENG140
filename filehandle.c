#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "usefulfunc.h"

int main()
{
	char* filepath;
	char* newname;
	char* oldname;
	char* tmp;
	char answer;
	FILE* newfile;
	int  length,i,j,k;
	
	
	while(1) {	
		k=0;
		printf("Enter the path of file:\n");
		//getchar();
		filepath=getIn();
		printf("%s\n",filepath);
		
		length=len(filepath);
		i=length-1;
		printf("%d\n",i);
	//searching for the target oldname	
		while (filepath[i]!='/' && i!=-1) i--;
		
		
	//creating oldnamed file
		
		tmp = malloc( sizeof(char)*(length-i));
		tmp[length]=0;
        if (!tmp) {
            free(oldname);
            oldname = NULL;
            break;
        }
        oldname = tmp;
		
		
		for (j=i+1;j<length;j++)
		{
			oldname[k]=filepath[j];
			k++;
		}
		printf("%s\n",oldname);
		
		//check if file exists
	if(!access(filepath,F_OK))
		{
			printf("File exists. Rename?(y/n):\n");
			
				scanf("%c",&answer);
				
				//renamefile if yes
				if (answer=='y')
				{
					printf("Write the new name of the file:\n");
					getchar();
					newname=getIn();
					
					printf("%s\n",newname);
					printf("%s\n",oldname);
					
					if(rename(oldname,newname)) printf("couldnt rename the file.\n");
					else printf("the file renamed successfully.\n");
				if(newname) free(newname);
				//if no, prompt for input
				}
				else  if (answer=='n')
				{
					getchar();
				}
		}
		
	//createfile if doesnt exist
		else
		{
			newfile=fopen(oldname,"w");
			fclose(newfile);
			if(newfile) printf("the file created successfully.\n");
			else printf("could not create the file.\n");
		}
	if(filepath) free(filepath);
	if(oldname) free(oldname);
	
	}

	return 0;
}
