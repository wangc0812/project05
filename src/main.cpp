#include <iostream>
#include "define.h"
#include "matrix.h"

using namespace std;

int main()
{
    Matrix<float> fmat(3,4);
    fmat.printMatrix();
    fmat.setElement(1,2,1.6666f);
    fmat.printMatrix();
    cout << fmat.getElement(1,2) << endl;
    return 0;
}