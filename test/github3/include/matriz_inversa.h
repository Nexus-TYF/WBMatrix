#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*
struct mmatrix
{
	double **M;
	int n, m;
};

struct mmatrix A;
*/

typedef struct
{
	double **M;
	int n, m;
} mmatrix;

void freematr(mmatrix *A);
mmatrix *memmatr(int filas, int columnas);
mmatrix *mulmat(mmatrix *A, mmatrix *B);
void printmmatrix(mmatrix *A);
void cofacmmatrix(mmatrix *A, mmatrix *D, int p, int q, int tam);
float determmatrix(mmatrix *A, int tam);
void adjmmatrix(mmatrix *A, mmatrix *Adj, int tam);
void invermmatrix(mmatrix *A);
