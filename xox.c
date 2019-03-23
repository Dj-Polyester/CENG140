#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "usefulfunc.h"

char** createTable(int m,int n)
{
	int i,j;
	char** table=(char**)malloc(m*sizeof(char*));
	for(i=0;i<m;++i)
	{
		table[i]=(char*)malloc(n*sizeof(char));
		for(j=0;j<n;++j)
		{
			table[i][j]=' ';
		}
	}
	
	return table;
}

void printTable(char** table,int m,int n)
{
	printf("\n");
	int j=0,i,index_int;
	float index;
	for(i=0;i<n;++i) printf(" %d",i);
	printf("\n");
	while(j < 2*m+1)
	{
		if(j%2==0)
		{
			for(i=0;i<n;++i) printf(" -");
		}
		else
		{
			for(i=0;i<n;++i)
			{
				index=(j-1)/2;
				index_int=(int)index;
				printf("|%c",table[index_int][i]);
			}
			printf("| %d",index_int);
		}
		printf("\n");
		++j;
	}
	printf("\n");
}

int findroundwinner(char** table,int m,int n,int win_occ,char ch)
{
	int count=1,i,j;
	//horizontal case
	for(i=0;i<m;++i)
		for(j=0;j<n-1;++j)
		{
			if(table[i][j]==ch && table[i][j+1]==ch) ++count;
			else count=1;
			if (count==win_occ) return 1;
		}
	count=1;
	//vertical case
	for(j=0;j<n;++j)
		for(i=0;i<m-1;++i)
		{
			if(table[i][j]==ch && table[i+1][j]==ch) ++count;
			else count=1;
			if (count==win_occ) return 1;
		}
	//cross case (left-right)
	count=1;
	i=n-win_occ;
	j=0;
	while(1)
	{
		if (table[j][i]==ch && table[j+1][i+1]==ch) ++count;
		else count=1;
		
		if (m<n)
		{
			if (i<=m-2 && j==m-2)
			{
				j-=(i-1);
				i=0;
			}
			else if(i==n-2 || j==m-2)
			{
				i-=(j+1);
				j=0;
			}
			else
			{
				++i;
				++j;
			}
		}
		else if(m>=n)
		{
			if (i==n-2 && j<n-2)
			{
				i-=(j+1);
				j=0;
			}
			else if (i==n-2 || j==m-2)
			{
				j-=(i-1);
				i=0;
			}
			else
			{
				++i;
				++j;
			}
		}
		if(count==win_occ) return 1;
		if (i==win_occ-2 && j==m-2) break;
	}
	//cross case (right-left)
	count=1;
	i=win_occ-1;
	j=0;
	while(1)
	{
		if(table[j][i]==ch && table[j+1][i-1]) ++count;
		else count=1;
		if(m<n)
		{
			if(i>=n-m+1 && j==m-2)
			{
				j-=(n-i-2);
				i=n-1;
			}
			else if(i==1 || j==m-2)
			{
				i+=(j+1);
				j=0;
			}
			else
			{
				--i;
				++j;
			}
		}
		else if(m>=n)
		{
			if(i==1 && j<n-2)
			{
				i+=(j+1);
				j=0;
			}
			else if(i==1 || j==m-2)
			{
				j-=(n-i-2);
				i=n-1;
			}
			else
			{
				i-=1;
				j+=1;
			}
		}
		if(count==win_occ) return 1;
		if(i==n-win_occ+1 && j==m-2) break;
	
	}
	return 0;
}

void shuffle(char *array, size_t n)
{
   time_t t;
   
   /* Intializes random number generator */
   srand((unsigned) time(&t));
   
    if (n > 1) 
    {
        size_t i;
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          char t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}

int takeinput(char* string,int var,int minvalue)
{
	int varname=0;
	while(1)
	{
		printf("%s%d): ",string,var);
		scanf("%d",&varname);
		getchar();
		if (varname>minvalue) break;
		printf("What the f*** are you doing? Entry must exceed %d\n",minvalue);
		if (!minvalue) printf("Then why did you choose to play?\n");
	
	}
	return varname;

}



int main()
{
	char** table;
	char character;
	int winner,scorebest,x,y;
	int game=takeinput("How many rounds? (at least ",1,0);
	int win_occ=takeinput("Win after how many occurences? (at least ",3,2);
	
	int m=takeinput("Enter column (at least ",win_occ,win_occ-1);
	int n=takeinput("Enter row (at least ",win_occ,win_occ-1);
	int playernum=takeinput("How many players? (at least ",1,0);
	
	//player names
	int i=0;
	char* ch=malloc(playernum*sizeof(char));
	int* scoreboard=calloc(playernum,sizeof(int));
	while(i < playernum)
	{
		printf("Alias of player (only one character) %d: ",i+1);
		scanf("%c",&ch[i]);
		getchar();
		++i;
	}

	//for (i=0;i<playernum;++i) printf("%c ",ch[i]);
	
	
	shuffle(ch,playernum);
	printf("\n################################################################################\n");
	printf("%c starts!!!",ch[0]);
	
	//number of rounds (<=game) and the only coefficient for scoring 
	int countround=1;
	//between rounds
	
	while (countround<=game)
	{
		int winner=0;
		int playerturn=0;
		
		//number of plays
		int playcount=0;
		
		table=createTable(m,n);
		//during a round
		while (1)
		{
			printf("%d. round:\n",countround);
			if (playerturn==playernum) playerturn-=playernum;
			character=ch[playerturn];
			printf("\n%c's turn\n",character);
			printTable(table,m,n);
			while (1)
			{
				
				printf("Enter the x coordinate: ");
				scanf("%d",&y);
				printf("Enter the y coordinate: ");
				scanf("%d",&x);
				
				if (x<m && y<n)
				{
					if (table[x][y]==' ')
					{
						table[x][y]=character;
						break;
					}
					else printf("The square is not empty, is indeed occupied!!!\n");
				}		
				else printf("Invalid coordinates. Out of bounds!!!\n");
			}
			scoreboard[playerturn]+=countround;
			++playerturn;
			if (playcount>=playernum*(win_occ-1))
			{
				for(i=0;i<playernum;++i)
				{
					if(findroundwinner(table,m,n,win_occ,ch[i]))
					{
						winner=ch[i];
						printTable(table,m,n);
						break;
					}
				}
				if(winner) break;
			}
			++playcount;
		}
		printf("\n=================================================================================\n");
		printf("%c wins the round!!!\n",winner);
		
		//SCOREBOARD AT THE END OF THE ROUND
		printf("SCOREBOARD:\n");
		
		for(i=0;i<playernum;++i)
		{
			printf("%c: %d\n",ch[i],scoreboard[i]);
		}
		
		++countround;
	}
	//find the winner of the game
	scorebest=nmax(scoreboard,playernum);
	winner=ch[scorebest];
	printf("\n################################################################################\n");
	
	printf("%c wins the game with a score of %d!!!\n",winner,scoreboard[scorebest]);
	
	//SCOREBOARD AT THE END OF THE GAME
	printf("SCOREBOARD:\n");
		
		for(i=0;i<playernum;++i)
		{
			printf("%c: %d\n",ch[i],scoreboard[i]);
		}
	
	
	for(i=0;i<m;++i) free(table[i]);
	free(table);
	
	free(ch);
	free(scoreboard);
	return 0;
}
