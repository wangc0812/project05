#include <iostream>
#include "define.h"
#include "matrix.hpp"

using namespace std;

int main()
{
    Matrix<float> fmat0(4,4);
    fmat0.setElement(0,1,1.6666);
    // fmat0.printMatrix();
    Matrix<float> fmat1(4,4);
    fmat1.setElement(0,0,1.6666);
    // fmat1.printMatrix();
    Matrix<float> sum = fmat0 + fmat1;
    // sum.printMatrix();
    // Matrix<float> dot = 10.0f * sum ;
    // dot.printMatrix();
    Matrix<float> pro1 = fmat1 * sum ;
    Matrix<float> pro2 = matmul(fmat1,fmat1);
    pro1.printMatrix();
    // pro2.printMatrix();
    // cout<<"row="<<pro1.shape(0)<<endl;
    // cout<<"col="<<pro1.shape(1)<<endl;
    // float * data = pro1.getValue();
    // int len = pro1.getEleNum();
    // sum = pro1;
    // sum.printMatrix();
    // Matrix<float> fmat2(4,4,data);
    // fmat2.printMatrix();
    // Matrix<float> fmat3(fmat0);
    // fmat3.printMatrix();

    // Matrix<float> ass (4,4);
    // ass = fmat2;
    // ass.printMatrix();

    return 0;
}