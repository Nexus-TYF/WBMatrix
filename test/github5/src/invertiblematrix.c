#include "invertiblematrix.h"

void freeMatrix(int n, int** array)
{
        int k = 0;
        for(k = 0; k < n; ++k)
        {
                free(array[k]);
        }
        free(array);
}

void printIdentityMatrix(int n, int** array)
{
        int i = 0;
        int j = 0;

        for(i = 0; i < n; ++i)
        {
                for(j = 0; j < n; ++j)
                {
                        printf("%d ",array[i][j]);
                }
                printf("\n");
        }
}

void printInvertibleMatrix(int n, int** array)
{
        int i = 0;
        int j = 0;

        for(i = 0; i < n; ++i)
        {
                for(j = 0; j < n; ++j)
                {
                        printf("%d\t",array[i][j]);
                }
                printf("\n");
        }
}

void getIdentityMatrix(int n, int** array)
{
        int r = 0;
        int c = 0;

        for(r = 0; r < n; ++r)
        {
                for(c = 0; c < n; ++c)
                {
                        if(r == c)
                                array[r][c] = 1;
                        else
                                array[r][c] = 0;
                }
        }

}

void getInvertibleMatrix(int n, int** array)
{
        int i = 0;
        int j = 0;
        int k = 0;
	int mainRowNum = 0;

        int* tempArray = NULL;

	srand((int)time(NULL));
	int transformTime = (int)(rand()%1000);
	//printf("We will do %d times tansformation.\n",transformTime);

        tempArray = (int*)malloc(sizeof(int)*n);

        for(i = 0; i < transformTime; ++i)
        {
		mainRowNum = (int)(rand()%(n-1));
                for(k = 0; k < n; ++k)
			if(((UINT16_MAX - (array[mainRowNum][k])*((int)(rand()%5 - 10))) < 0) || ((UINT16_MAX*(-1)) - (array[mainRowNum][k])*((int)(rand()%5 - 10)) > tempArray[k]))
				tempArray[k] = (array[mainRowNum][k]);
			else
                        	tempArray[k] = (array[mainRowNum][k])*((int)(rand()%5 - 10));

                for(j = 0; j < n; ++j)
                        if(mainRowNum != j)
                                for(k = 0; k < n; ++k)
				{
					if(((UINT16_MAX - array[j][k]) < tempArray[k]) || ((UINT16_MAX*(-1)) - array[j][k] > tempArray[k]))
						array[j][k] = array[j][k]/4;
					else
						array[j][k] = array[j][k] + tempArray[k];
				}
        }

        free(tempArray);
}

int putIdentityMatrixIntoFile(int n, int** array)
{
        FILE* fp = NULL;
        int i = 0;
        int j = 0;

        if((fp = fopen("input","w"))==NULL)
        {
                printf("Error: writing file error!\n");
                return -1;
        }

        for(i = 0; i < n; ++i)
        {
                for(j = 0; j < n; ++j)
                {
                        if(j != (n-1))
                                fprintf(fp,"%d ", array[i][j]);
                        else
                                fprintf(fp,"%d", array[i][j]);
                }
                fputs("\n",fp);
        }

        fclose(fp);

        return 1;
}

int putInvertibleMatrixIntoFile(int n, int** array)
{
        FILE* fp = NULL;
        int i = 0;
        int j = 0;

        if((fp = fopen("input","w"))==NULL)
        {
                printf("Error: writing file error!\n");
                return -1;
        }

        for(i = 0; i < n; ++i)
        {
                for(j = 0; j < n; ++j)
                {
                        if(j != (n-1))
                                fprintf(fp,"%d\t", array[i][j]);
                        else
                                fprintf(fp,"%d", array[i][j]);
                }
                fputs("\n",fp);
        }

        fclose(fp);

        return 1;

}