#include <iostream>
#include "define.h"
#include "matrix.hpp"


using namespace std;

int main()
{
    float *data = new float[20];
    memset(data, 0, 20*sizeof(float));
    Matrix<float> fmat1(5, 4, data);
    fmat1.setElement(0,1,1.6f);
    fmat1.setElement(1,0,1.5f);
    fmat1.printMatrix();

    {Matrix<float> fmat5 = fmat1.ROI(1,0,4,2);
    fmat5.printMatrix();}
    
// use copy constructor
    {Matrix<float> fmat2 = fmat1;
    fmat2.printMatrix();
    fmat1.printMatrix();}
// use operator =
    Matrix<float> fmat3;
    fmat3 = fmat1;
    fmat3.printMatrix();

    // Matrix<float> fmat4(2, 4, data);
    // fmat4.setElement(1,1,1.6f);
    // fmat4.printMatrix();

    // Matrix<float> fmat5 = fmat1 + fmat4;
    // fmat5.printMatrix();

    // Matrix<float> fmat6 = fmat1 - fmat4;
    // fmat6.printMatrix();

    // Matrix<float> fmat7 = fmat1 * 3;
    // fmat7.printMatrix();

    // Matrix<float> fmat8(4, 2, data);
    // fmat8.setElement(1,1,1.6f);
    // fmat8.printMatrix();
    // Matrix<float> fmat9 = fmat1 * fmat8;
    // fmat9.printMatrix();

    // Matrix<float> fmat10 = 3 * fmat1;
    // fmat10.printMatrix();

    // cout<<"The length of row of the fmat10: "<<fmat10.shape(0)<<endl;
    // cout<<"The length of column of the fmat10: "<<fmat10.shape(1)<<endl;

    return 0;
}