#include<stdio.h>
#include<stdlib.h>

double **augmentedmatrix;
double temporary, r;
int i, j, k, dimension, temp; 
FILE *file;
FILE *fileOut;

void makeMatrix();
void read();
void write();
void augmentingmatrix();
void findPivo();
void swapLine();
void calcInverse();