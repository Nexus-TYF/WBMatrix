#ifndef INVERSEMATRIX_H

#define INVERSEMATRIX_H

typedef struct{
  float**      elements;
  unsigned int dimension;
}QMatrix;

int initQMatrix(QMatrix* matrix, const unsigned int dimension);
int qMatrixScanf(QMatrix* matrix);
int qMatrixPrintf(QMatrix matrix);
int qMatrixSwapRows(QMatrix* matrix,
                    const unsigned int row1,
                    const unsigned int row2);
int qMatrixSwapColumns(QMatrix* matrix,
                       const unsigned int column1,
                       const unsigned int column2);
float qMatrixMainElementLQ(QMatrix matrix,
                         const unsigned int limiter,
                         int* mainElementRow,
                         int* mainElementColumn);
float* qMatrixExtractRow(QMatrix matrix, const unsigned int row);
int multiplyRow(float* row, float scalar, int dimension);
int subtractRowQMatrix(QMatrix matrix,
                       int minuendRow,
                       float* subtrahend,
                       int limiter);
int initEQMatrix(QMatrix* matrix, const unsigned int dimension);
QMatrix reverseMatrix(QMatrix matrix); /* Spoils 'matrix' reducing it to
                                          elementary*/

#endif /* inverseMatrix.h */
