//Program to solve a set of linear equations using LU decomposition
//Required functions imported from custom library "mylib"
#include <stdio.h>
#include "mylib.h"


int main()
{
	printf("Please enter the number of variables in the equations: ");
	int var;
	scanf("%d", &var);
	float mat[4][4];
	float constant[4];
	float sol[4] = { 0 };	//to store solution
	FILE* temp1 = fopen("A4q1.txt", "r");
	if (temp1 == NULL)
		exit(1);

	//reading input into coefficient and constant matrix
	for (int i = 0; i < var; i++)
	{
		for (int j = 0; j < var + 1; j++)
		{
			if (j < var)
				fscanf(temp1, "%f ", &mat[i][j]);
			else
				fscanf(temp1, "%f ", &constant[i]);
		}
	}

	printf("Matrix representation for given set of equations is:\n ");
	for (int i = 0; i < var; i++)
	{
		for (int j = 0; j < var; j++)
		{
			printf(" %d", (int)(mat[i][j]));
		}
		printf("   x%d", i + 1);
		printf(" = %f", constant[i]);
		printf("\n ");
	}

	//performing required operations
	LUdecompose(var, mat);
	LUsolution(var, mat, constant, sol);

	//printing solution
	printf("\nUsing the method of LU decomposition, the solution is:\n");
	for (int i = 0; i < var; i++)
	{
		printf("\n x%d=%f\n", i + 1, sol[i]);
	}
}






/**************OUTPUT***************************************
Please enter the number of variables in the equations: 4
Matrix representation for given set of equations is:
  1 0 1 2   x1 = 6.000000
  0 1 -2 0   x2 = -3.000000
  1 2 -1 0   x3 = -2.000000
  2 1 3 -2   x4 = 0.000000

Using the method of LU decomposition, the solution is:

 x1=1.000000

 x2=-1.000000

 x3=1.000000

 x4=2.000000
 ************************************************************/
