#ifndef  __MATRIX_H__
#define  __MATRIX_H__

#include <iostream>
#include "define.h"
#include <string.h>
#include <iomanip>



// Class Matrix define

class Matrix
{
private:

    size_t row, column, size;
    float* value;
    
public:

    // Constructor
    Matrix();
    Matrix(int row, int col, float val);
    Matrix(const Matrix &rhs);

    // Deconstructor
    ~Matrix();

    // Print matrix
    void printMatrix();

};

// Constructor

Matrix::Matrix()
{
    row = 0;
    column =0;
    size = 0;
    value = NULL;   
}

Matrix::Matrix(int r, int c, float val) : row(r), column(c)
{
    if (row <= 0 || column <= 0)
    {
        ERROR_INPUT_INPUTPARA;
        std::cout << "This error happened in constructor" << std::endl;
    }
    else
    {
        size = row * column;
        value = new float[size];

        for(size_t i = 0; i < size; i++)
        {
         value[i] = val;
        }

        std::cout << "constructor used" << std::endl;
    }

}

// Deconstructor

Matrix::~Matrix()
{
    if (value != NULL)
    {
        delete[] value;
        value = NULL;
    }

    std::cout << "deconstructor used" << std::endl;
        
}

void Matrix:: printMatrix() 
{
    if(this != NULL)
    {
        std::cout<< "---------------matrix print start----------------" <<std::endl;
        
        size_t i, j;
        for (i = 0; i < row; i++) 
        {
            for (j = 0; j < column; j++)
            {
                std::cout << std::setprecision(5) << this->value[i * (this->column) + j]<<" " ;
            }

        std::cout << std::endl;
        }

        std::cout<< "---------------matrix print end----------------" <<std::endl;
    }
    else
    {
        ERROR_INPUT_POINTER;
        std::cout << "This error happened in printMatrix()" << std::endl;
    }

}


#endif