#include "matrixinverse.h"

/*Aloca o espaço de memória para armazenar a matriz aumentada*/
void makeMatrix() {
	int i;
    augmentedmatrix = (double **)malloc(sizeof(double)*dimension);
    for(i = 0; i < dimension; i++) {         
        augmentedmatrix[i] = (double *)malloc(sizeof(double)*dimension*2);     
    }
}

/*Faz a leitura da mariz a partir do arquivo de entrada*/
void read(){
	for(i=0; i<dimension; i++)
		for(j=0; j<dimension; j++)
			fscanf(file,"%lf",&augmentedmatrix[i][j]);
}

/*Escreve a matriz inversa no arquivo de saida*/
void write(){
	for(i=0; i<dimension; i++){
		for(j=dimension; j<2*dimension; j++)
			fprintf(fileOut,"%.5lf ",augmentedmatrix[i][j]);
		fprintf(fileOut,"\n");
	}
}

/*Gera os valores da matriz aumentada adicionando a matriz identidade no fim da matriz de entrada*/
void augmentingmatrix(){
	for(i=0;i<dimension; i++)
		for(j=dimension; j<2*dimension; j++)
			if(i==j%dimension) augmentedmatrix[i][j]=1;
			else augmentedmatrix[i][j]=0;
}

/*Encontra o proximo elemento que vai ser utilizado como pivô*/
void findPivo(){
	temp=j;
	for(i=j+1; i<dimension; i++)
		if(augmentedmatrix[i][j]>augmentedmatrix[temp][j])
			temp=i;
}

/*Realiza a troca de linhas se o pivô não pertencer a linha atual*/
void swapLine(){
	if(temp!=j)
		for(k=0; k<2*dimension; k++){
			temporary=augmentedmatrix[j][k];
			augmentedmatrix[j][k]=augmentedmatrix[temp][k];
			augmentedmatrix[temp][k]=temporary;
	}
}

/*Realiza o calculo dos novos valores para cada linha da matriz aumentada, gerando a matriz inversa*/
void calcInverse(){
	for(i=0; i<dimension; i++)
		if(i!=j){ //verifica se é a linha atual.
			r=augmentedmatrix[i][j];
			for(k=0; k<2*dimension; k++)
				augmentedmatrix[i][k]-=(augmentedmatrix[j][k]/augmentedmatrix[j][j])*r; //calcula o novo valor para as linhas diferentes da atual.
		}else {
			r=augmentedmatrix[i][j];
			for(k=0; k<2*dimension; k++)
				augmentedmatrix[i][k]/=r; //divide os elementos da linha atual pelo pivô.
		}
}