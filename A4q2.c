//Program to find the inverse of a matrix using LU decomposition
//Required functions imported from custom library "mylib"

#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"


int main()
{
	int var = 4;
	float mat[4][4];
	FILE* temp1 = fopen("a4-q2.txt", "r");
	if (temp1 == NULL)
		exit(1);

	for (int i = 0; i < var; i++)
	{
		for (int j = 0; j < var; j++)
		{
			fscanf(temp1, "%f ", &mat[i][j]);
		}
	}

	printf("\nThe matrix A is:\n");
	for (int i = 0; i < var; i++)
	{
		for (int j = 0; j < var; j++)
		{
			printf("%d   ", (int)(mat[i][j]));
		}
		printf("\n");
	}

	float permute[4][4];			//permutation matrix for pivoting
	for (int i = 0; i < var; i++)
	{
		for (int j = 0; j < var; j++)
		{
			if (i == j)
				permute[i][j] = 1;
			else
				permute[i][j] = 0;
		}
	}
	
	//verifying existence of inverse
	float det = 0;
	det = determinant(mat, var);
	printf("\nThe determinant for the given matrix is : %f", det);
	
	if (det == 0)
	{
		printf("\nThe inverse doesnot exist.");
		exit(0);
	}
	else
		printf("\nThe inverse exists.");

	//performing necessary computations
	LUpivot(mat, permute, var);
	LUdecompose(var, mat);

	//finding inverse
	float inv[4][4] = { 0 };
	LUinverse(mat,permute, inv, var);

	//printing results
	printf("\n\nUsing LU decomposition, the inverse of A is:\n");
	for (int i = 0; i < var; i++)
	{
		for (int j = 0; j < var; j++)
		{
			printf("%f   ",(inv[i][j]));
		}
		printf("\n");
	}
}






/*******************OUTPUT***************************

The matrix A is:
0   2   8   6
0   0   1   2
0   1   0   1
3   7   1   0

The determinant for the given matrix is : -36.000000
The inverse exists.

Using LU decomposition, the inverse of A is:
-0.250000   1.666666   -1.833333   0.333333
0.083333   -0.666667   0.833333   0.000000
0.166667   -0.333333   -0.333333   0.000000
-0.083333   0.666667   0.166667   0.000000

******************************************************/
