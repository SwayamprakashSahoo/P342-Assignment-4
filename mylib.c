#include "mylib.h"
#include <stdlib.h>
//function to perform LU decomposition on a matrix and store it in the same matrix
void LUdecompose(int var, float mat[4][4])
{
	for (int k = 0; k < var; k++)
	{
		for (int j = k; j < var; j++)
		{
			float sum = 0;
			for (int p = 0; p < k; p++)
			{
				sum += mat[k][p] * mat[p][j];
			}
			mat[k][j] = (mat[k][j] - sum);
		}
		for (int i = k + 1; i < var; i++)
		{
			float sum = 0;
			for (int p = 0; p < k; p++)
			{
				sum += mat[i][p] * mat[p][k];
			}
			mat[i][k] = (mat[i][k] - sum) / mat[k][k];
		}
	}
}

//function to find the solution from the LU decomposition
void LUsolution(int var, float mat[4][4], float constant[4], float sol[4])
{
	float y[4] = { 0 };
	for (int i = 0; i < var; i++)
	{
		float sum = 0;
		for (int k = 0; k < i; k++)
		{
			sum += mat[i][k] * y[k];
		}
		y[i] = (constant[i] - sum);
	}
	for (int i = var - 1; i >= 0; i--)
	{
		float sum = 0;
		for (int k = i + 1; k < var; k++)
		{
			sum += mat[i][k] * sol[k];
		}
		sol[i] = (y[i] - sum) / mat[i][i];
	}
}

//Function to perform row-wise pivoting of the matrix
void LUpivot(float mat[4][4],float permute[4][4], int var)
{
	for (int i = 0; i < var - 1; i++)
	{
		if (mat[i][i] == 0)
		{
			for (int j = i + 1; j < var; j++)
			{
				if (abs(mat[j][i]) > mat[i][i])
				{
					for (int k = 0; k < var; k++)
					{
						float temp1 = mat[i][k];
						mat[i][k] = mat[j][k];
						mat[j][k] = temp1;
						float temp2 = permute[i][k];
						permute[i][k] = permute[j][k];
						permute[j][k] = temp2;
						continue;
					}
				}
			}
		}
	}
}

//function to find determinant of a matrix
float determinant(float mat[4][4], int n)
{
	float Minor[4][4];
	int c1, c2;
	float det;
	float c[4];
	float O = 1;
	det = 0;
	if (n == 2)
	{
		det = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
		return det;
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			c1 = 0, c2 = 0;
			for (int j = 0; j < n; j++)
			{
				for (int k = 0; k < n; k++)
				{
					if (j != 0 && k != i)
					{
						Minor[c1][c2] = mat[j][k];
						c2++;
						if (c2 > n - 2)
						{
							c1++;
							c2 = 0;
						}
					}
				}
			}
			det = det + O * (mat[0][i] * determinant(Minor, n - 1));
			O = -1 * O;
		}
	}
	return det;
}

//function to find inverse using LU decomposition
void LUinverse(float mat[4][4], float permute[4][4], float inv[4][4], int var)
{
	for (int i = 0; i < var; i++)
	{
		float temp[4] = { 0 };
		for (int j = 0; j < var; j++)
			temp[j] = permute[j][i];
		float y[4];
		for (int j = 0; j < var; j++)
		{
			float x = 0.0;
			for (int k = 0; k <= j - 1; k++)
			{
				x = x + mat[j][k] * y[k];
			}
			y[j] = (temp[j] - x);
		}

		for (int j = var - 1; j >= 0; j--)
		{
			float x = 0.0;
			for (int k = j + 1; k < var; k++)
			{
				x = x + mat[j][k] * inv[k][i];
			}
			inv[j][i] = (y[j] - x) / mat[j][j];
		}
	}
}

//function for pivoting for Gauss-Jordan elimination
void pivot(float mat[][20], int var)
{
	for (int i = 0; i < var - 1; i++)
	{
		if (mat[i][i] == 0)
		{
			for (int j = i + 1; j < var; j++)
			{
				if (abs(mat[j][i]) > mat[i][i])
				{
					for (int k = i; k < var + 1; k++)
					{
						float temp = mat[i][k];
						mat[i][k] = mat[j][k];
						mat[j][k] = temp;
						continue;
					}
				}
			}
		}
	}
}

//function for solve for solution using Gauss-Jordan elimination and print it
void GaussJordan(float mat[][20], int var)
{
	for (int i = 0; i < var; i++)
	{
		pivot(mat, var);
	}

	float c, x[20];
	for (int j = 0; j < var; j++)
	{
		for (int i = 0; i < var; i++)
		{
			if (i != j)
			{
				c = mat[i][j] / mat[j][j];
				for (int k = 0; k < var + 1; k++)
				{
					mat[i][k] = mat[i][k] - c * mat[j][k];
				}
			}
		}
	}
	printf("\nThe solution is:\n");
	for (int i = 0; i < var; i++)
	{
		x[i] = mat[i][var] / mat[i][i];
		printf("\n x%d=%f\n", i + 1, x[i]);
	}
}

//function to multiply two matrices
void Matrix_mult(float mat[][20], float inv[][20], int var)
{
	float product[20][20];
	printf("\nThe product of matrix A and its inverse is:\n");
	for (int i = 0; i < var; i++)
	{
		for (int j = 0; j < var; j++)
		{
			product[i][j] = 0;
			for (int k = 0; k < var; k++)
				product[i][j] = product[i][j] + mat[i][k] * inv[k][j];
			printf("%d ", (int)(product[i][j]));
		}
		printf("\n");
	}
}

