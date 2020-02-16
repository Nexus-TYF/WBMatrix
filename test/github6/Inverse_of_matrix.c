////////////////////////////////////////////////////////////////////////////////////////

//Header Files.
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdint.h>

#ifdef __GNUC__
#include <x86intrin.h>
#endif
#ifdef _MSC_VER
#include <intrin.h>
#endif
#pragma intrinsic(__rdtsc)

//Repeat test times and calculate on average for accuracy
#define TEST 100

//CPU cycles set start;
uint64_t start_rdtsc()
{
	return __rdtsc();
}

//CPU cycles set end;
uint64_t end_rdtsc()
{
    return __rdtsc();
}
////////////////////////////////////////////////////////////////////////////////////////
																					
//Function to calculate Determinant of the Matrix.
int determinant(int *matrix, int order)
{
	int *Minor = (int *)malloc(order * order * sizeof(int));		//Matrix to calculate Minor
   int i,j,runloop,row,col;
   int det=0;																	//Initialize determinant as Zero
   int sign=1;																	//Initialize sign as 1 initially as first i=element needs to be positive while calculating determinant.
	if(order == 1)
   {
   	return(*(matrix));													//return the determinant value for Single Element.
   }
   else
	{
		for(runloop = 0 ; runloop < order ; runloop++)				//need to run the loop order number of times.
   	{
      	row = 0, col = 0;													//Initialize row and column for Minor Matrix as (0,0).
      	for(i = 0 ; i < order ; i++)									//Loop to go through rows.
      	{
   	   	for(j = 0 ; j < order ; j++)								//Loop to go through columns.
         	{
     	   		*((Minor+i*(order-1))+j)=0;							//Initialize corresponding Minor element as Zero.
            	if(i != 0 && j != runloop)								//Consider only the elements which are not in the same row and column of considered minor.
            	{
            		*((Minor+row*(order-1))+col) = *((matrix+i*order)+j);			//Assign value to Minor from Main Matrix.
            		col++;													//Go to next column.
            		if(col > order-2)										//If column exceeds the Minor Matrix size.
               	{
               		row++;												//Go to next row.
               		col=0;												//Go to first column of next row. 
               	}
					}
				}
			}
         det = det + (sign * ((*(matrix+runloop)) * (determinant(Minor,order-1))));	//Recursive function to call the same function again with Minor size.
         sign=-1*sign;
		}
	}
   free(Minor);																//Free the allocated memory.
   return (det);																//Return the value of determinant.
}
//End of Function Determinant.

////////////////////////////////////////////////////////////////////////////////////////

//Function to calculate Transpose of the Cofactor Matrix.
void transpose(int *matrix,float *in,int order)
{
	int row,col,det;
	float *temp1 = (float *)malloc(order * order * sizeof(float));			//Temporary matrix to store the transpose matrix.
	float *inverse = (float *)malloc(order * order * sizeof(float));		//Temperory matrix to store the inverse matrix.
	for (row = 0;row < order; row++)													//Loop for going to next row.
   {
   	for (col = 0;col < order; col++)												//Loop for going to next column.
     	{
      	(*((temp1+row*order)+col)) = (*((in+col*order)+row));				//Saving the transpose by using row=col and col=row.
      }
	}
  	det = determinant(matrix, order);												//Calculate determinant of matrix.
	for (row = 0;row < order; row++)													//Loop for going to next row.
   {
   	for (col = 0;col < order; col++)												//Loop for going to next column.
      {
      	(*((inverse+row*order)+col)) = (*((temp1+row*order)+col)) / det;//Calculating and storing inverse in temperory matrix.
        	(*((in+row*order)+col))=(*((inverse+row*order)+col));				//Assign to Inverse matrix
		}
	}
	free(temp1);																			//Free the allocated memory.
	free(inverse);																			//Free the allocated memory.
}
//End of Function Transpose.

////////////////////////////////////////////////////////////////////////////////////////

//Function to calculate the Cofactor Matrix.
void cofactor(int *matrix, int order, float *in)
{
	int rowmain,colmain,rowcofactor,colcofactor,row,col;
	int *factor = (int *)malloc(order * order * sizeof(int));	//Temporary matrix to store the factor matrix.
	int *temp2 = (int *)malloc(order * order * sizeof(int));		//Temporary matrix to calculate the cofactor matrix.
		
	for(rowmain=0;rowmain<order;rowmain++)								//Loop for going to next row of main matrix.
	{
		for(colmain=0;colmain<order;colmain++)							//Loop for going to next column of main matrix.
		{
			rowcofactor=0;														//Initialize row for cofactor matrix as 0.
			colcofactor=0;														//Initialize column for cofactor matrix as 0.
			for(row=0;row<order;row++)										//Loop for going to next row.
			{
				for(col=0;col<order;col++)									//Loop for going to next column.
				{
					(*((temp2+row*(order-1))+col))=0;					//Initialize value of corresponding element as Zero.
					if(rowmain != row && colmain != col)				//Consider only the elements which are not in the same row and column of considered matrix.
					{
						(*((temp2+rowcofactor*(order-1))+colcofactor))=(*((matrix+row*order)+col));//Assign value to temporary matrix.
						colcofactor++;											//Go to next column.
						if(colcofactor>order-2)								//If the column size of matrix is exceeded.
							{
								colcofactor=0;									//Go to first column of next row.
								rowcofactor++;									//Go to next row.
							}	
					}
				}
			}
			(*((factor+rowmain*order)+colmain)) = (pow(-1, rowmain + colmain)) * determinant(temp2, order - 1);	//Calculate inverse.
			(*((in+rowmain*order)+colmain))=(*((factor+rowmain*order)+colmain));		//Assign values to the inverse matrix.
			
		}
	}
	transpose(matrix,in,order);
	free(factor);																//Free the allocated memory.
	free(temp2);																//Free the allocated memory.
}
//End of Function Cofactor.

////////////////////////////////////////////////////////////////////////////////////////

//Function to multiply Matrix
void multi(int *matrix, float *in,float *multiply,int order)
{
	int c,d,k;
	float sum=0;
		 
	for (c = 0; c < order; c++) 											//Loop for matrix multiplication.
	{
  		for (d = 0; d < order; d++) 										//Loop for matrix multiplication.
		{
        	for (k = 0; k < order; k++) 									//Loop for matrix multiplication.
			{
         	sum = sum + (*((matrix+c*order)+k)) * (*((in+k*order)+d));	//Calculate sum of multiplied elements.
        	}
 
        	*((multiply+c*order)+d) = sum;								//Assign values to multiply matrix.
			sum = 0;
		}
	}
}
//End of Function multiply.

////////////////////////////////////////////////////////////////////////////////////////

//Function to print Matrix
void print(float *multiply, int order)
{
	int row,col;
	for(row=0;row<order;row++)												//Loop for going to next row.
	{
		for(col=0;col<order;col++)											//Loop for going to next column.
		{
			printf("%f ", *((multiply+row*order)+col)); 				//print elements of one row in single line.
		}
		printf("\n");															//next row in new line.		
	}	
}
//End of Function print.

////////////////////////////////////////////////////////////////////////////////////////
int a8[8][8]={
{0,1,0,1,0,0,0,1},
{1,1,0,0,1,0,1,1},
{0,1,1,1,1,0,1,0},
{1,1,0,1,0,1,0,0},
{1,0,0,0,1,0,0,1},
{0,1,0,0,1,0,1,1},
{1,1,1,0,1,0,1,1},
{1,1,0,0,0,0,0,1}
};

//Start of main().
int main()
{
	uint64_t begin;
    uint64_t end;
    uint64_t ans = 0;
    int i;

	int order=8;
	float in[order][order];	
	printf("inverse_of_matrix Method performance test:\n");																		//Enters only when determinant is NOT Zero.
	begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
	{
		cofactor(&a8[0][0],order,&in[0][0]);						//Function call to calculate cofactor.						
	}	
	end = end_rdtsc();
    ans = (end - begin);
    printf("compute 8*8 inverse matrix cost %llu CPU cycles\n", (ans) / TEST);
	return 0;	
}
//End of main().

////////////////////////////////////////////////////////////////////////////////////////
