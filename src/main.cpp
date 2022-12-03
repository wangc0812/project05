#include <iostream>
#include "define.h"
#include "matrix.h"

using namespace std;

int main()
{
    Matrix<float> fmat0(3,4);
    fmat0.setElement(0,1,1.6666f);
    fmat0.printMatrix();
    Matrix<float> fmat1(3,4);
    fmat1.setElement(0,0,1.6666f);
    fmat1.printMatrix();
    Matrix<float> sum = fmat0 + fmat1;
    sum.printMatrix();
    Matrix<float> sub = sum - fmat1;
    sub.printMatrix();

    return 0;
}