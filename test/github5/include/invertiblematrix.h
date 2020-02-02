#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

void freeMatrix(int n, int** array);
void printIdentityMatrix(int n, int** array);
void printInvertibleMatrix(int n, int** array);
void getIdentityMatrix(int n, int** array);
void getInvertibleMatrix(int n, int** array);
int putInvertibleMatrixIntoFile(int n, int** array);
int putIdentityMatrixIntoFile(int n, int** array);