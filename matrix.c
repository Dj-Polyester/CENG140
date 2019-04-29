#include <stdio.h>
#include <stdlib.h>


double** matrix(int m,int n)
{
	double **matrix;
	int i;
	matrix=(double**)malloc(m*sizeof(double*));
	for(i=0;i<m;++i)
	{
		matrix[i]=malloc(n*sizeof(double));
	}

	return matrix;
}


void fillmatrix(double***matrix,int m,int n)
{
	int i,j;	

	for(i=0;i<m;++i)
	{
		for(j=0;j<n;++j)
		{
			printf("%d. row %d. column: ",i,j);
			scanf("%lf",&(*matrix)[i][j]);
		}
	}
}

void printmatrix(double**matrix,int m,int n)
{
	int i,j;	

	for(i=0;i<m;++i)
	{
		for(j=0;j<n;++j)
		{
			printf("%lf",matrix[i][j]);
		}
		printf("\n");
	}
}

void freematrix(double** matrix,int m,int n)
{
	int i;
	
	for(i=0;i<m;++i)
	{
		free(matrix[i]);
	}
	free(matrix);
}


int main()
{	
	int m,n;	
	double** ma;
	printf("print rows and columns:");	
	scanf("%d %d",&m,&n);

	ma=matrix(m,n);
	fillmatrix(&matrix,m,n);
	printmatrix(matrix,m,n);

	freematrix(matrix,m,n);

	return 0;
}
