# WBMatrix

An Optimized Matrix Library for White-Box Block Cipher
Implementations

Contains the matrix operations related to the white-box block cipher implementation and provides thorough test cases for their performance and accuracy. The test cases also include the Chow et al.'s [white-box AES](https://link.springer.com/chapter/10.1007/3-540-36492-7_17) and Xiao-Lai's [white-box SM4](http://gb.oversea.cnki.net/KCMS/detail/detailall.aspx?filename=2010204831.nh&dbcode=CMFD&dbname=CMFD2010) implementations built by WBMatrix, [NTL](https://www.shoup.net/ntl/), and [M4RI](https://github.com/malb/m4ri), respectively.

## Applications
1. [CEJO White-box AES](https://github.com/Nexus-TYF/CEJO-whitebox-AES)

2. [Table Redundancy Method for White-box AES](https://github.com/Nexus-TYF/Table-Redundancy-Method-for-White-box-AES)

3. [Xiao-Lai White-box SM4](https://github.com/Nexus-TYF/Xiao-Lai-White-box-SM4)

4. [Xiao-Lai-White-box-AES](https://github.com/Nexus-TYF/Xiao-Lai-White-box-AES)

## Clone

git clone --depth 1 https://github.com/Nexus-TYF/WBMatrix

## Matrix Library

### Supports For Following Operations (4/8/16/32/64/128 bits)

* Matrix-Vector multiplication<br>
* Matrix-Matrix multiplication<br>
* Generation of an invertible Matrix with its inverse matrix (pairwise invertible matrices)<br>
* Generation of the pairwise invertible affine transformations<br>
* Matrix transpositon<br>
* Affine transformation<br>
* Encodings concatenation<br>
* Encodings conversion<br>

### Header Files

* **WBMatrix.h** The declaration of the main functions.<br>
* **struture.h** Data structure of matrix and affine function.<br>
* **random.h** For random functions.<br>

### Main Functions (8bit in Example)

* **affineU8(Aff8 aff, uint8_t arr)** affine transformation for an uint8_t number **arr**, and returns an uint8_t result.<br>
* **affinemixM8(Aff8 aff, Aff8 preaff_inv, Aff8 \*mixaff)** affine conversion between **aff** and **preaff_inv**, result is set in **mixaff**.<br>
* **affinecomM8to32(Aff8 aff1, Aff8 aff2, Aff8 aff3, Aff8 aff4, Aff32 \*aff)** affine concatenation, the matrix part of **aff** consists of submatrices on its diagonal, while the vector part of **aff** consists of subvectors.<br>
* **copyM8(M8 Mat1, M8 \*Mat2)** replicates the matrix **Mat1** to **Mat2**.<br>
* **flipbitM8(M8 \*Mat, int i, int j)** flips the (i, j) bit in matrix **Mat**.<br>
* **genMatpairM8(M8 \*Mat, M8 \*Mat_inv)** generates an invertible matrix **Mat** and its inverse matrix **Mat_inv**.<br>
* **genaffinepairM8(Aff8 \*aff, Aff8 \*aff_inv)** generates an affine transformation **aff** and its inversion **aff_inv**.<br>
* **identityM8(M8 \*Mat)** converts the matrix **Mat** into an identity matrix.<br>
* **invsM8(M8 Mat, M8 \*Mat_inv)** calculates the inversion of **Mat** by Gaussian elimination method, result is set in **Mat_inv**.<br>
* **isinvertM8(M8 Mat)** determines if the matrix is invertible (1 for positive).<br>
* **MatMulVecM8(M8 Mat, V8 Vec, V8 \*ans)** multiplication for a matrix **Mat** and a vertor **Vec**, result is set in **ans**.<br>
* **MatMulNumM8(M8 Mat, uint8_t n)** multiplication for a matrix **Mat** and a number **n**, returns a number.<br>
* **MatMulMatM8(M8 Mat1, M8 Mat2, M8 \*Mat)** multiplication for a matrix **Mat1** and a matrix **Mat2**, result is set in **Mat**.<br>
* **MatAddMatM8(M8 Mat1, M8 Mat2, M8 \*Mat)** addition between the matrix **Mat1** and **Mat2**, result is set in **Mat**.<br>
* **MattransM8(M8 Mat, M8 \*Mat_trans)** transpositon for a matrix **Mat**, result is set in **Mat_trans**.<br>
* **readbitM8(M8 Mat, int i, int j)** extracts the (i, j) bit in matrix **Mat**.<br>
* **setbitM8(M8 \*Mat, int i, int j, int bit)** assigns the (i, j) bit a value **bit**.<br>

### Code Examples

M8 mat\[3\]; //defines an 8-bit matrix<br>
genMatpairM8(&mat\[0\], &mat\[1\]); //generates the pairwise invertible matrices<br>
MatMulMatM8(mat\[0\], mat\[1\], &mat\[2\]); //matrix-matrix multiplication<br>
printM8(mat\[2\]); //prints the matrix<br>

### Included library

1. [RandomSequence](https://github.com/preshing/RandomSequence)

---

## Test Cases

### Folder Introduction

* **github1_M4RI** The performance test for matrix operation and for the generation of pairwise invertible matirces by M4RI library.<br>
* **github(x)** The performance test for the generation of invertible matrix or the computation of invertion by the implementations on Github.<br>
* **NTL** The matirx The performance test for matrix operation and for the generation of pairwise invertible matirces by NTL library.<br>
* **randomness** A Statistical Test Suite for Random and Pseudorandom Number Generators for Cryptographic Applications (NIST Special Publication 800-22
Revision 1a). <br>
* **WBAES** A Chow et al.'s white-box AES implementation and its performance test built by WBMatrix, NTL, and M4RI respectively.<br>
* **WBSM4** A Xiao-Lai's white-box SM4 implementation and its performance test built by WBMatrix, NTL, and M4RI respectively.<br>

### File Introduction

* **Accuracy_test.c** Accuracy test for the matrix operations in WBMatrix.<br>
* **BasisMatrixMethod_test.c** Performance test for the generation of pairwise invertible matrices by Basis Matrix Method.<br>
* **RGEMethod_test.c** Performance test for the generation of pairwise invertible matrices by [Reverse Gaussian Elimination Method](https://csce.ucmss.com/cr/books/2018/LFS/CSREA2018/MSV4017.pdf).<br>
* **RLUDMethod_test.c** Performance test for the generation of pairwise invertible matrices by [Reverse LU Decomposition Method](https://csce.ucmss.com/cr/books/2018/LFS/CSREA2018/MSV4017.pdf).<br>
* **WBGEMethod_test.c** Performance test for the generation of pairwise invertible matrices by Randomly Generate and Verify Method and Gaussian Elimination method.<br>
* **WBMatrixMatOp_test.c** Performance test for the matrix operations in WBMatrix.<br>
* **WBMatrixMethod_test.c** Performance test for the generation of pairwise invertible matrices by WBMatrix Method.<br>

### Build

```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

### Run

```
$ ./WBMM
```

### Included libraries

1. [NTL](https://www.shoup.net/ntl/)<br>
2. [M4RI](https://github.com/malb/m4ri)<br>
3. [SMx-SM4](https://github.com/NEWPLAN/SMx/tree/master/SM4)<br>
4. [WhiteBoxAES](https://github.com/Gr1zz/WhiteBoxAES)<br>
5. [sp800_22_tests](https://github.com/dj-on-github/sp800_22_tests)<br>
6. [Inverse-matrix](https://github.com/md-akhi/Inverse-matrix.git)<br>
7. [Inverse-Matrix](https://github.com/jsgonzlez661/Inverse-Matrix.git)<br>
8. [parallelMatrixInversion](https://github.com/moabrj/parallelMatrixInversion.git)<br>
9. [InvertibleMatrix](https://github.com/liuyunhao13467/InvertibleMatrix.git)<br>
10. [Inverse-of-Matrix](https://github.com/kay-max/Inverse-of-Matrix.git)<br>
11. [inverseMatrix](https://github.com/braindrillmd/inverseMatrix.git)<br>

---
Last Updated : 2020/08/01<br>
Modified By : Nexus

---
Details of update:<br>
(2019/12/9)<br>
1. Changes the generation of an invertible matrix from an initialized matrix
(now just supports for 8/32bits operations)<br>
2. Unifies the API<br>
3. User can change the generation times in inverse.h <br>
4. Uses initinvbaseM(8/32)() function to generate an initialized invertible matrix and its trails are recorded in basetrailM(8/32)<br>
8bits default value is 10<br>
32bits default value is 30<br>
which represent the operation times.<br>
5. If not use the initialized function then each matrix is generated from an identify matrix in defined times<br>
6. New: Add copy function to replace the identify function.<br>

(2019/12/10)<br>
1. New: Add 16/64/128bits inverse matrix function.<br>
New method has been covered.<br>

(2019/12/11)<br>
1. New: 16/64bit affine transformation.<br>
2. New: 128bit affine transformation.<br>
No retrun value because of its special structure.

(2019/12/12)<br>
1. New: 16/64/128bit affine combination operation.<br>

(2019/12/16)<br>
1. New: header files for defination of the matices.<br>

(2019/12/17)<br>
1. Fixed: some errors.<br>
2. New: Add the parameters for initializing the intermediate matrix function. <br>
inverse.h has the max times and min times for selection.<br>

(2020/01/08)<br>
1. New: Add Matrix addition function.<br>

(2020/01/10)<br>
1. File tidying.<br>
2. New: Add WBMatrix test.<br>
3. New: Add Matrix Basis Method test.<br>

(2020/01/12)<br>
1. New: Add 128bit test for matrix basis method.<br>

(2020/01/18)<br>
1. Updates the test case: generate invertible matrix , compute inverse matrix.<br>
2. New: Invertible funcions: Matrix Basis Method, WBMatrix Method, Reverse Gaussian Elimination Method.<br>
3. New: Inverse functions: WBMatrix Method, Matrix Basis Method.<br>

(2020/01/20)<br>
1. New: Add CMakeLists.txt<br>
2. New: Add M4RI Method.<br>

(2020/01/21)<br>
1. Organizes file structure, especially fix the structure.h and .c error.<br>

(2020/01/22)<br>
1. Deletes xor.h.<br>

(2020/01/30)<br>
1. New: Add Gaussian elimination Method (Based on WBMatrix).<br>
2. Changes the generation function of random Matrix.<br>

(2020/01/31)<br>
1. New: Add Reverse LU Decomposition Method.<br>

(2020/02/01)<br>
1. Fixed: Function of random matrix.<br>

(2020/02/02)<br>
1. New: Comparison test on github.<br>
2. New: Accuracy Test.<br>
3. Fixed: Parameter Orders of affinemix function.<br>

(2020/02/07)<br>
1. Fixed: Multipe defination of global variables.<br>
2. New: Function for random seed.<br>
3. New: WBAES.<br>

(2020/02/09)<br>
1. Fixed: Poor randomness of random matrix function.<br>
2. New: Function for estimating the invertibility of matrix.<br>

(2020/02/16)<br>
1. New: Add new test cases from github.<br>

(2020/03/05)<br>
1. New: Add performance test cases on M4RI: basic arithmetic with matrix .<br>
2. New: Add performance test cases on NTL.<br>
3. New: Add performance test cases on WBMatrix.<br>

(2020/03/06)<br>
1. New: Add vector addition funcion.<br>
2. Fixed: Accuracy test mode.<br>
3. Optimized: Replace rotation with logical-AND.<br>

(2020/03/07)<br>
1. New: WBAES by M4RI.<br>

(2020/03/09)<br>
1. Update: WBMatrix Library for WBAES.<br>

(2020/03/10)<br>
1. New: WBSM4 by M4RI.<br>
2. Fixed: the release version of WBAES (WBMatrix version).<br>
3. New: WBSM4 by WBMatrix.<br>

(2020/03/11)<br>
1. New: WBSM4 by NTL.<br> 
2. Update: Clean-up NTL files.<br>

(2020/03/15)<br>
1. New: Release on github.<br> 

(2020/04/15)<br>
1. New: supports for returning Hamming Weight.<br> 
2. New: Add an example for mitigating DCA attack.<br>

(2020/06/22)<br>
1. New: Add the references of articles and implementations.<br>
2. Fixed: Errors of random function in Linux.<br>

(2020/06/25)<br>
1. New: Add randomness test cases (Special Publication 800-22
Revision 1a).<br>

(2020/07/01)<br>
1. Fixed: Update the random functions.<br>

(2020/07/31)<br>
1. New: Update the new method for generating the pairwise invetible matrices.<br>
2. New: Add bitwise operation (read/flip/set) function.<br>
3. New: Add the function for calculating the inversion of an invertible matrix by Gaussian elimination method.<br>

(2020/08/01)<br>
1. New: Support for 4-bit matrix operations.<br>
2. New: Add 8to64, 8to128, 16to64, 32to128, 16to128 concatenation functions.<br>

(2020/08/02)<br>
1. Fixed: Errors of comments in misc.c.<br>