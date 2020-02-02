#include "matriz_inversa.h"
//mmatrix A; A.n es equivalente (&A)->n
// mmatrix *X; X->n es equivalente a (*X).n
void freematr(mmatrix *A) // Liberar memoria 
{
	if (A)
	{
		if (A->M != 0)
		{
			for (int i = 0; i < A->n; ++i)
				free(A->M[i]);
			free(A->M);
		}
		free(A);
	}
}

mmatrix *memmatr(int filas, int columnas) // Asignacion del tamaño de la matriz
{
	int i;
	mmatrix *A;
	A = (mmatrix*)malloc(sizeof(mmatrix));
	if (!A) return 0;
	A->n = filas;
	A->m = columnas;
	A->M = (double**)malloc(filas*sizeof(double*));
	if (A->M == 0) return 0;
	for (i = 0; i < filas; ++i)
	{
		A->M[i] = (double*)malloc(columnas*sizeof(double));
		if (A->M[i] == 0)
		{
			A->n = i;
			freematr(A);
			return 0;
		}
	}
	return A;
}

mmatrix *mulmat(mmatrix *A, mmatrix *B) // Multiplicacion de matrices
{
	mmatrix *C;
	if (A->m != B->n) return 0;
	C = memmatr(A->n, B->m);
	if (C)
	{
		for (int j = 0; j < A->n; ++j)
			for (int i = 0; i < B->m; ++i)
			{
				C->M[j][i] = 0.0;
				for (int k = 0; k < A->m; ++k)
					C->M[j][i] += A->M[j][k]*B->M[k][i];
			}
	}
	return C;
}

void printmmatrix(mmatrix *A) // Imprime la matriz
{
	int i, j;
	for (i = 0; i < A->n; ++i)
	{
		for (j = 0; j < A->m; ++j)
			printf ("\t%g", (A->M[i][j] == -0.0) ? 0: A->M[i][j]);
		printf("\n");
	}
}

void cofacmmatrix(mmatrix *A, mmatrix *D, int p, int q, int tam) // Cofactor de la matriz
{
	int i, j, k = 0, w = 0;

	for (i = 0; i < tam; ++i)
		for (j = 0; j < tam; ++j)
			if (i != p && j != q)
			{
				D->M[k][w++] = A->M[i][j];
				if (w == (tam-1))
				{
					w = 0;
					k++;
				}
			}
}


float determmatrix(mmatrix *A, int tam) // Determinante de una matriz
{
	int i, j, signo = 1;
	float determ=0;
	mmatrix *D;

	if(A->n == A->m)
	{
		if (tam == 1) return A->M[0][0];
		if (tam == 2) return (A->M[0][0]* A->M[1][1]- A->M[0][1]* A->M[1][0]);
		else 
		{
			D = memmatr(A->n, A->m);
			for (i = 0; i < tam; ++i)
			{
				cofacmmatrix(A, D, 0, i, tam);          
				determ += signo*A->M[0][i]*determmatrix(D, (tam - 1));
				signo = -signo;
			}
			freematr(D);
		}
		return determ;
	}
}

void adjmmatrix(mmatrix *A, mmatrix *Adj, int tam) // Adjunta de una matriz
{
	mmatrix *E;
	int i, j, signo2 = 1;

	if (tam == 1) Adj->M[0][0] = 1;

	for (i = 0; i < tam; ++i)
		for (j = 0; j < tam; ++j)
		{
			E = memmatr(A->n, A->m);
			cofacmmatrix(A, E, i, j, tam);
			signo2 = ((i + j) % 2 == 0) ? 1: -1;
			Adj->M[j][i] = (signo2) * (determmatrix(E, (tam - 1)));
		}
	freematr(E);
}

void invermmatrix(mmatrix *A) // Inversa de una matriz
{
	mmatrix *Adj, *inverA;
	float determt;
	int i, j;

	if (A->n == A->m)
	{
		determt = determmatrix(A, A->n);
		if (determt == 0) printf("La matrix no tiene inversa\n");
		else
		{
			inverA = memmatr(A->n, A->m);
			Adj = memmatr(A->n, A->m);
			adjmmatrix(A, Adj, A->n); // llamar la funcion para la adjunta de la matriz
			for (i = 0; i < A->n; ++i)
				for (j = 0; j < A->n; ++j)
					inverA->M[i][j] = Adj->M[i][j]/determt; // Calculo de la inversa 
			//printf("\nLa matriz inversa es: \n");
			//printmmatrix(inverA);
			freematr(Adj);
			freematr(inverA);
		}
	}
	else printf("La matriz no es cuadrada\n");
}