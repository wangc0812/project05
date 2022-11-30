#include <iostream>
#include "define.h"
#include "matrix.h"

using namespace std;

int main()
{
    Matrix mat1 = Matrix(2,4,1.1);
    mat1.printMatrix();
    return 0;
}