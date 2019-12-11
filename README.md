WBMatrix
====

Matrix Mathematical Operation Library Of White Box Cryptography
----

Support for following operations(8/16/32/64/128 bits):<br>
Matrix-Vector multiplication<br>
Matrix-Matrix multiplication<br>
Generate invertible Matrix with it's inverse matrix<br>
Matrix transpositon<br>
Affine transformation<br>

---
inverse.h : Revisable generate times from the temporary state matrix.<br>
struture.h : Data structure of matrix.<br>
structure.c : Prestored identity matrix.<br>
xor.h : Prestored value for number's internal xor.<br>

---
last update : 2019/12/11<br>
modified by : Nexus

---
details(2019/12/9):<br>
1.Change the generation of invertible matrix to base on a initialized matrix
(now just support for 8/32bits operations)<br>
2.Unify the API<br>
3.User can change the generation times in inverse.h <br>
4.Use initinvbaseM(8/32)() function to generate a initialized invertible matrix and it's trails are recorded in basetrailM(8/32)<br>
8bits default value is 15<br>
32bits default value is 30<br>
which represent the operation times.<br>
5.If not use the initialize fucntion then each matrix generate from a identify matrix in defined times<br>
6.Add copy function instead of identify function.<br>

---
(2019/12/10):<br>
1.Update 16/64/128bits inverse matrix function.<br>
New method has been covered.<br>

---
(2019/12/11):<br>
1.Add 16/64bit affine transformation.<br>




