# WBMatrix

An Optimized Matrix Library for White-Box Block Cipher
Implementations

Contains the matrix operations related to the white-box block cipher implementation and provides thorough test cases for their performance and accuracy. The test cases also include the Chow et al.'s [white-box AES](https://link.springer.com/chapter/10.1007/3-540-36492-7_17) and Xiao-Lai's [white-box SM4](http://gb.oversea.cnki.net/KCMS/detail/detailall.aspx?filename=2010204831.nh&dbcode=CMFD&dbname=CMFD2010) implementations built by WBMatrix, [NTL](https://www.shoup.net/ntl/), and [M4RI](https://github.com/malb/m4ri), respectively.

## Applications
1. [CEJO White-box AES](https://github.com/Nexus-TYF/CEJO-whitebox-AES)

2. [Table Redundancy Method for White-box AES](https://github.com/Nexus-TYF/Table-Redundancy-Method-for-White-box-AES)

3. [Xiao-Lai White-box SM4](https://github.com/Nexus-TYF/Xiao-Lai-White-box-SM4)

4. [Xiao-Lai White-box AES](https://github.com/Nexus-TYF/Xiao-Lai-White-box-AES)

5. [Improved Masking for White-box AES](https://github.com/Nexus-TYF/Improved-Masking-for-White-box-AES)

6. [WBMatrix based LowMC](https://github.com/Nexus-TYF/WBMatrix-based-LowMC)

7. [Bai-Wu White-box SM4](https://github.com/Nexus-TYF/Bai-Wu-White-box-SM4)

## Clone

```
$ git clone --depth 1 https://github.com/Nexus-TYF/WBMatrix
```

## Matrix Library

### Supports For Following Operations (4/8/16/32/64/128/256 bits)

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
* **struture.h** Data structure of the matrix and affine functions.<br>
* **random.h** The declaration of the random functions.<br>

### Main Functions (8bit in Example)

* **affineU8(Aff8 aff, uint8_t arr)** affine transformation for an uint8_t number **arr**, and returns an uint8_t result.<br>
* **affinemixM8(Aff8 aff, Aff8 preaff_inv, Aff8 \*mixaff)** affine conversion between **aff** and **preaff_inv**, result is set in **mixaff**.<br>
* **affinecomM8to32(Aff8 aff1, Aff8 aff2, Aff8 aff3, Aff8 aff4, Aff32 \*aff)** affine concatenation, the matrix part of **aff** consists of the submatrices on its diagonal, while the vector part of **aff** consists of the subvectors.<br>
* **copyM8(M8 Mat1, M8 \*Mat2)** replicates the matrix **Mat1** to **Mat2**.<br>
* **flipbitM8(M8 \*Mat, int i, int j)** flips the (i, j) bit in matrix **Mat**.<br>
* **genMatpairM8(M8 \*Mat, M8 \*Mat_inv)** generates an invertible matrix **Mat** and its inverse matrix **Mat_inv**.<br>
* **genaffinepairM8(Aff8 \*aff, Aff8 \*aff_inv)** generates an affine transformation **aff** and its inversion **aff_inv**.<br>
* **identityM8(M8 \*Mat)** converts the matrix **Mat** into an identity matrix.<br>
* **invsM8(M8 Mat, M8 \*Mat_inv)** calculates the inversion of **Mat** by Gaussian elimination method, result is set in **Mat_inv**.<br>
* **isinvertM8(M8 Mat)** determines if the matrix is invertible (1 for positive).<br>
* **MatMulVecM8(M8 Mat, V8 Vec, V8 \*ans)** multiplication between a matrix **Mat** and a vertor **Vec**, result is set in **ans**.<br>
* **MatMulNumM8(M8 Mat, uint8_t n)** multiplication between a matrix **Mat** and a number **n**, returns a number.<br>
* **MatMulMatM8(M8 Mat1, M8 Mat2, M8 \*Mat)** multiplication between a matrix **Mat1** and a matrix **Mat2**, result is set in **Mat**.<br>
* **MatAddMatM8(M8 Mat1, M8 Mat2, M8 \*Mat)** addition between the matrix **Mat1** and **Mat2**, result is set in **Mat**.<br>
* **MattransM8(M8 Mat, M8 \*Mat_trans)** transpositon for a matrix **Mat**, result is set in **Mat_trans**.<br>
* **readbitM8(M8 Mat, int i, int j)** extracts the (i, j) bit in matrix **Mat**, returns 0/1.<br>
* **setbitM8(M8 \*Mat, int i, int j, int bit)** assigns the (i, j) bit a value **bit** (0/1).<br>
* **initM8(M8 *Mat)** converts all the elements of the matrix **Mat** into 0.<br>
* **randM8(M8 *Mat)** generates a random matrix **Mat**.<br>
* **printbitM8(M8 Mat)** prints all the elements of the matrix **Mat**.<br>
* **isequalM8(M8 Mat1, M8 Mat2)** determines if the matrix **Mat1** is equal to **Mat2** (1 for positive).<br>
* **initV8(V8 *Vec)** converts all the elements of the vector **Vec** into 0.<br>
* **randV8(V8 *Vec)** generates a random vector **Vec**.<br>
* **VecAddVecV8(V8 Vec1, V8 Vec2, V8 *Vec)** addition between the vector **Vec1** and **Vec2**, result is set in **Vec**.<br>
* **HWU8(uint8_t n)** calculates the Hamming Weight of a number **n**.<br>

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

* **github1_M4RI** The performance test for matrix operation and for the generation of the pairwise invertible matirces by M4RI library.<br>
* **github(x)** The performance test for the generation of an invertible matrix or the computation of its invertion by the implementations on Github.<br>
* **NTL** The performance test for matrix operation and for the generation of the pairwise invertible matirces by NTL library.<br>
* **randomness** A Statistical Test Suite for Random and Pseudorandom Number Generators for Cryptographic Applications (NIST Special Publication 800-22
Revision 1a). <br>
* **WBAES** A Chow et al.'s [white-box AES](https://link.springer.com/chapter/10.1007/3-540-36492-7_17) implementation and its performance test built by WBMatrix, NTL, and M4RI respectively.<br>
* **WBSM4** A Xiao-Lai's [white-box SM4](http://gb.oversea.cnki.net/KCMS/detail/detailall.aspx?filename=2010204831.nh&dbcode=CMFD&dbname=CMFD2010) implementation and its performance test built by WBMatrix, NTL, and M4RI respectively.<br>

### File Introduction

* **Accuracy_test.c** Accuracy test for the matrix operations in WBMatrix.<br>
* **BasisMatrixMethod_test.c** Performance test for the generation of the pairwise invertible matrices by Basis Matrix Method.<br>
* **LowMCMethod_text.cpp** Performance test for the generation of the pairwise invertible matrices by [LowMC Method](https://eprint.iacr.org/2016/687) and Gaussian Elimination method.<br>
* **RGEMethod_test.c** Performance test for the generation of the pairwise invertible matrices by [Reverse Gaussian Elimination Method](https://csce.ucmss.com/cr/books/2018/LFS/CSREA2018/MSV4017.pdf) and Gaussian Elimination method.<br>
* **RLUDMethod_test.c** Performance test for the generation of the pairwise invertible matrices by [Reverse LU Decomposition Method](https://csce.ucmss.com/cr/books/2018/LFS/CSREA2018/MSV4017.pdf) and Gaussian Elimination method.<br>
* **WBGEMethod_test.c** Performance test for the generation of the pairwise invertible matrices by Randomly Generate and Verify Method and Gaussian Elimination method.<br>
* **WBMatrixMatOp_test.c** Performance test for the matrix operations in WBMatrix.<br>
* **WBMatrixMethod_test.c** Performance test for the generation of the pairwise invertible matrices by WBMatrix Method.<br>

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
12. [lowmc](https://github.com/LowMC/lowmc)<br>

---
Last Updated : 2021/01/12<br>
WBMatrix Version: 3.3.0

---
Upgrade history:<br>
(2019/12/9)<br>
1. Added: An invertible matrix is generated from an initialized matrix. (now just supports for 8/32bits operations)<br>
2. Fixed: Unifies the API.<br>
3. Added: The adjustable generation times in inverse.h.<br>
4. Added: Uses initinvbaseM(8/32)() function to generate an initialized invertible matrix and its trails are recorded in basetrailM(8/32).<br>
8bits default value is 10,<br>
32bits default value is 30,<br>
which represent the operation times.<br>
5. Added: If not use the initialized function then each matrix is generated from an identity matrix with the default times.<br>
6. Added: Copy function to replace the identify function.<br>

(2019/12/10)<br>
1. Added: 16/64/128bits inverse matrix functions.<br>
New method has been covered.<br>

(2019/12/11)<br>
1. Added: 16/64bit affine transformation.<br>
2. Added: 128bit affine transformation.<br>
No retrun value because of its special structure.<br>

(2019/12/12)<br>
1. Added: 16/64/128bit affine combination operation.<br>

(2019/12/16)<br>
1. Added: the header files for a defination of the matices.<br>

(2019/12/17)<br>
1. Fixed: Error fixes.<br>
2. Added: The parameters for initializing the intermediate matrix function.<br>
inverse.h has the max times and min times for selection.<br>

(2020/01/08)<br>
1. Added: Matrix addition function.<br>

(2020/01/10)<br>
1. Improved: File tidying.<br>
2. Added: WBMatrix test.<br>
3. Added: Matrix Basis Method test.<br>

(2020/01/12)<br>
1. Added: 128bit test for matrix basis method.<br>

(2020/01/18)<br>
1. Added: Updates the test case of the generation of an invertible matrix and the computation of its inverse matrix.<br>
2. Added: Invertible funcions: Matrix Basis Method, WBMatrix Method, Reverse Gaussian Elimination Method.<br>
3. Added: Inverse functions: WBMatrix Method, Matrix Basis Method.<br>

(2020/01/20)<br>
1. Added: CMakeLists.txt<br>
2. Added: M4RI Method.<br>

(2020/01/21)<br>
1. Improved: Organizes file structure, especially fixs the structure.h and .c errors.<br>

(2020/01/22)<br>
1. Improved: Deletes xor.h.<br>

(2020/01/30)<br>
1. Added: Gaussian elimination Method (Based on WBMatrix).<br>
2. Improved: Changes the generation function of a random Matrix.<br>

(2020/01/31)<br>
1. Added: Reverse LU Decomposition Method.<br>

(2020/02/01)<br>
1. Improved: Functions for the generation of a random matrix.<br>

(2020/02/02)<br>
1. Added: Comparison test on github.<br>
2. Added: Accuracy Test.<br>
3. Improved: Parameter Orders of the affinemix function.<br>

(2020/02/07)<br>
1. Fixed: Multipe defination of the global variables.<br>
2. Added: Function for random seed.<br>
3. Added: WBAES.<br>

(2020/02/09)<br>
1. Fixed: Poor randomness of the random matrix function.<br>
2. Added: Function for estimating the invertibility of a matrix.<br>

(2020/02/16)<br>
1. Added: New test cases from github.<br>

(2020/03/05)<br>
1. Added: Performance test cases of M4RI: basic arithmetic with matrix.<br>
2. Added: Performance test cases of NTL.<br>
3. Added: Performance test cases of WBMatrix.<br>

(2020/03/06)<br>
1. Added: Vector addition funcion.<br>
2. Fixed: Accuracy test mode.<br>
3. Improved: Replaces the rotation with a logical-AND.<br>

(2020/03/07)<br>
1. Added: WBAES by M4RI.<br>

(2020/03/09)<br>
1. Added: WBAES by WBMatrix.<br>

(2020/03/10)<br>
1. Added: WBSM4 by M4RI.<br>
2. Fixed: The release version of WBAES (WBMatrix version).<br>
3. Added: WBSM4 by WBMatrix.<br>

(2020/03/11)<br>
1. Added: WBSM4 by NTL.<br> 
2. Improved: Clean-up NTL files.<br>

(2020/03/15)<br>
1. Added: Release on github.<br> 

(2020/04/15)<br>
1. Added: Supports for returning Hamming Weight.<br> 
2. Added: An example for mitigating DCA attack.<br>

(2020/06/22)<br>
1. Added: The references of the articles and implementations.<br>
2. Fixed: Errors of the random function in Linux.<br>

(2020/06/25)<br>
1. Added: Randomness test cases (Special Publication 800-22 Revision 1a).<br>

(2020/07/01)<br>
1. Fixed: Updates the random functions.<br>

(2020/07/31)<br>
1. Added: Updates the new method for generating the pairwise invetible matrices.<br>
2. Added: Bitwise operation (read/flip/set) functions.<br>
3. Added: The function for calculating the inversion of an invertible matrix by Gaussian elimination method.<br>

(2020/08/01)<br>
1. Added: Supports for 4-bit matrix operations.<br>
2. Added: 8to64, 8to128, 16to64, 32to128, 16to128 concatenation functions.<br>

(2020/08/09)<br>
1. Fixed: Errors of the comments in misc.c.<br>
2. Added: 4-bit test cases.<br>

(2020/08/10)<br>
1. Added: Supports for C++.<br>
2. Added: LowMC Method.<br>

(2020/08/24)<br>
1. Fixed: Free from C99.<br>

(2020/09/29)<br>
1. Added: A new matrix transposition function.<br>

(2021/01/12)<br>
1. Added: Supports for partial 256-bit operations.<br>
2. Added: Partial 256-bit test cases.<br>