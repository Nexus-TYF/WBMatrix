#include <stdio.h>
#include <conio.h>
#include <math.h>

int cin(float a[100][100]);
void cout(float a[100][100],int n,int show);
void minor(float b[100][100],float a[100][100],int i,int n);
float det(float a[100][100],int n);
void transpose(float c[100][100],float d[100][100],float n,float det);
void cofactor(float a[100][100],float d[100][100],float n,float determinte);
void inverse(float a[100][100],float d[100][100],int n,float det);