WBMatrix
====

White-Box Matrix Library(Designed for White-Box Cryptography)
----

* Support For Following Operations(8/16/32/64/128 bits):<br>
* Matrix-Vector multiplication<br>
* Matrix-Matrix multiplication<br>
* Generate invertible Matrix with it's inverse matrix<br>
* Matrix transpositon<br>
* Affine transformation<br>

---
###Header Files:<br>
* **inverse.h** : Revisable generate times from the temporary state matrix , the selection times for initialization of base matrix.<br>
* **WBMatrix.h** : The declaration of the main function.<br>
* **struture.h** : Data structure of matrix.<br>

---
###Main Function(8bit in Example):<br>
* **initinvbaseM8(int N)** : initial base invertible matrix which generate in N times.<br>
we give a suggestion for the selection of N in inverse.h .<br>
* **genMatpairM8(M8 *Mat,M8 *Mat_inv)** : generate an invertible matrix Mat and its inverse matrix Mat_inv from the base matrix in prestored times set in inverse.h.<br>
* **genaffinepairM8(Aff8 *aff,Aff8 *aff_inv)** : generate an affine transformation aff and its inverse affine transformation aff_inv.<br>
* **MatMulVecM8(M8 Mat,V8 Vec,V8 *ans)** : multiplication for matrix Mat and vertor Vec, result set in ans.<br>
* **MatMulMatM8(M8 Mat1,M8 Mat2,M8 *Mat)** : multiplication for matrix Mat1 and matrix Mat2, result set in Mat.<br>
* **MattransM8(M8 Mat,M8 *Mat_trans)** : transpositon for matrix Mat, result set in Mat_trans.<br>
* **affineU8(Aff8 aff,uint8_t arr)** : affine transformation for an uint8_t number, and return an uint8_t result.

---
###Example:<br>
M32 mat32[3];<br>
initinvbaseM32(initM32_max);<br>
genMatpairM32(&mat32[0],&mat32[1]);<br>
MatMulMatM32(mat32[0],mat32[1],&mat32[2]);<br>
printM32(mat32[2]);<br>

---
Last Updated : 2019/02/09<br>
Modified By : Nexus

---
Details:<br>
(2019/12/9)<br>
1.Change the generation of invertible matrix to base on an initialized matrix
(now just support for 8/32bits operations)<br>
2.Unify the API<br>
3.User can change the generation times in inverse.h <br>
4.Use initinvbaseM(8/32)() function to generate a initialized invertible matrix and it's trails are recorded in basetrailM(8/32)<br>
8bits default value is 10<br>
32bits default value is 30<br>
which represent the operation times.<br>
5.If not use the initialize fucntion then each matrix generate from a identify matrix in defined times<br>
6.New: copy function instead of identify function.<br>

(2019/12/10)<br>
1.Update 16/64/128bits inverse matrix function.<br>
New method has been covered.<br>

(2019/12/11)<br>
1.New: 16/64bit affine transformation.<br>
2.New: 128bit affine transformation.<br>
No retrun value because of its special structure.

(2019/12/12)<br>
1.New: 16/64/128bit affine combination operation.<br>

(2019/12/16)<br>
1.New: header files define code.<br>

(2019/12/17)<br>
1.Fix some errors.<br>
2.New: Add parameter for initial base matrix function. <br>
The initial base matrix function has a max times and a min times for selection which is detailed in inverse.h .<br> 

(2019/01/08)<br>
1.New: Add Matrix addition function.<br>

(2019/01/10)<br>
1.File tidying.<br>
2.New: Add WBMatrix test.<br>
3.New: Add Matrix Basis Method test.<br>

(2019/01/12)<br>
1.New: Add 128bit test for matrix base method.<br>

(2019/01/18)<br>
1.Update test case: generate invertible matrix , compute inverse matrix.<br>
2.Invertible: Matrix Basis Method, WBMatrix Method, Reverse Gaussian Elimination Method.<br>
3.Inverse: WBMatrix Method, Matrix Basis Method.<br>

(2019/01/20)<br>
1.New: Add CMakeLists.txt<br>
2.New: Add M4RI Method.<br>

(2019/01/21)<br>
1.Organize file structure, especially fix the structure.h and .c error.<br>

(2019/01/22)<br>
1.Delete xor.h.<br>

(2019/01/30)<br>
1.New: Add Gaussian elimination Method(Base on WBMatrix).<br>
2.Change the generation function of random Matrix.<br>

(2019/01/31)<br>
1.New: Add Reverse LU Decomposition Method.<br>

(2019/02/01)<br>
1.Fixed: Function of random matrix.<br>

(2019/02/02)<br>
1.New: Comparison test on github.<br>
2.New: Accuracy Test.<br>
3.Fixed: Parameter Order of affinemix function.<br>

(2019/02/07)<br>
1.Fixed: Multipe define of global variables.<br>
2.New: Function for random seed.<br>
3.New: WBAES.<br>

(2019/02/09)<br>
1.Fixed: Poor randomness of random matrix function.<br>
2.New: Function for estimate the invertibility of matrix.<br>