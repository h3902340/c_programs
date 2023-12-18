#include <stdio.h>
#include <stdlib.h>

int printMatrix(int m, int n, double **matrix)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}

double **createMatrix(int m, int n)
{
    double *values = calloc(n * m, sizeof(double));
    double **matrix = malloc(n * sizeof(double *));
    for (int i = 0; i < m; ++i)
    {
        matrix[i] = values + i * n;
    }
    return matrix;
}

// Gauss-Jordan Elimination O(n^3)
double **getInverse(int n, double matrix[n][n])
{
    double **copy = createMatrix(n, n * 2);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            copy[j][i] = matrix[j][i];
        }
    }
    for (int i = n; i < n * 2; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j + n)
            {
                copy[j][i] = 1;
            }
            else
            {
                copy[j][i] = 0;
            }
        }
    }

    // find the first zero entry
    int i, j;
    int found;
    for (i = 0; i < n; i++)
    {
        found = -1;
        for (j = i; j < n; j++)
        {
            if (found != -1)
            {
                double ratio = copy[j][i] / copy[found][i];
                for (int k = i; k < n * 2; k++)
                {
                    copy[j][k] -= copy[found][k] * ratio;
                }
                continue;
            }
            if (copy[j][i] == 0)
                continue;
            found = j;
        }
        if (found != -1)
        {
            double pivot = copy[found][i];
            for (int k = i; k < n * 2; k++)
            {
                double temp = copy[found][k] / pivot;
                copy[found][k] = copy[i][k];
                copy[i][k] = temp;
            }
        }
    }
    for (int i = n - 1; i >= 0; i--)
    {
        if (copy[i][i] == 0)
            continue;
        for (int j = 0; j < i; j++)
        {
            double ratio = copy[j][i];
            for (int k = i; k < n * 2; k++)
            {
                copy[j][k] -= copy[i][k] * ratio;
            }
        }
    }

    double **inverse = createMatrix(n, n);
    for (int i = n; i < n * 2; i++)
    {
        for (int j = 0; j < n; j++)
        {
            inverse[j][i - n] = copy[j][i];
        }
    }
    return inverse;
}

int main()
{
    int n = 4;
    double matrix[4][4] = {
        {-15, -6, 5, 9},
        {-12, 9, 4, -2},
        {20, 8, 1, -12},
        {18, -2, -6, 3}};

    int zero_count = 0;
    double **inverse = getInverse(n, matrix);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (inverse[i][j] < 0.000001 && inverse[i][j] > -0.000001)
            {
                zero_count++;
            }
        }
    }
    printMatrix(n, n, inverse);
    printf("zero entry count: %d", zero_count);
    return 0;
}