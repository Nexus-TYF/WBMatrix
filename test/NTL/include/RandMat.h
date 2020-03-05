#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <vector>
#include <NTL/mat_GF2.h>

using namespace std;
using namespace NTL;

class RandMat {
  public:
  	RandMat();
    void init(int dim, int is_mb = 1);
    friend ostream& operator<< (ostream& stream, const RandMat& rMat);
    int dim;
    mat_GF2 mat;
    mat_GF2 invMat;
};
void InvTMat(mat_GF2& A, int dim);
void initVec(vec_GF2& V, int dim);


#endif // UTILS_HPP