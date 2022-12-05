#ifndef  __MATRIX_H__
#define  __MATRIX_H__

#include <iostream>
#include "define.h"
#include <string.h>
#include <iomanip>


// Class Matrix define
template <typename T>
class Matrix
{    
private:

    size_t _row, _column, _size;
    T * _elem;
    
public:

    // Constructor
    Matrix()
    {
        release();
        std::cout << "default constructor used" << std::endl; 
    }

    Matrix(size_t r, size_t c) : _row(r), _column(c)
    {
        if (r == 0 || c == 0 )
        {
            ERROR_INPUT_INPUTPARA;
            std::cout << "This error happened in constructor" << std::endl;
            return NULL;
        }
        else
        {
            _size = _row * _column;
            _elem = new T[_size];

            if (_elem == NULL)
            {
                std::cout << "failed to allocate memory for matrix data" << std::endl;
                free(_elem);
                return NULL;
            }
            
            memset(_elem, 0, _size * sizeof(T));
            std::cout << "constructor used" << std::endl;

        }

    }

    Matrix(size_t r, size_t c, * data)

    Matrix(const Matrix &rhs);
    
    bool create(size_t size,  const T * data)
    {
        release();

        if (size == 0)
        {
            std::cout << "ERROR: matrix size is zero" << std::endl;
            return false;
        }

        if(data == NULL)
        {
            std::cout << "input data invalid" << std::endl;
            return false;
        }
        
        this -> _size = size;

        if(this -> _size != 0)
        {
            this -> _elem = new T[this -> _size];
        }

        if (_elem == NULL)
        {
            std::cout << "failed to allocate memory for matrix data" << std::endl;
            free( _elem);
            return false;
        }

        memcpy(this -> _elem, data, this -> _size);

        return true;
    }

    bool release()
    {
        this -> _row = 0;
        this -> _column = 0;
        this -> _size = 0;

        if(this -> _elem != NULL)
        {
            delete [] this -> _elem;
            this -> _elem = NULL;
        }

        return true;
    }

    // Deconstructor
    ~Matrix()
    {
        if (_elem != NULL)
        {
            delete[] _elem;
            _elem = NULL;
        }

        std::cout << "deconstructor used" << std::endl;
            
    }

    // Print Matrix or Elems
    void printMatrix() const
    {
        if(this != NULL)
        {
            std::cout<< "---------------Matrix Print Start----------------" <<std::endl;
            
            size_t i, j;
            for (i = 0; i < _row; i++) 
            {
                for (j = 0; j < _column; j++)
                {
                    std::cout << this->_elem[i * (this->_column) + j]<<" " ;
                }

            std::cout << std::endl;
            }

            std::cout<< "---------------Matrix Print End----------------" <<std::endl;
        }
        else
        {
            ERROR_INPUT_POINTER;
            std::cout << "This error happened in printMatrix()" << std::endl;
        }

    }

     T getElement(size_t r, size_t c) const
    {
        if ( r >= this->_row || c >= this->_column )
        {
            std::cerr << "getElement(): Indices are out of range" << std::endl;
            return 0;
        }
        return _elem[ this->_column * r + c];
    }

    bool setElement(size_t r, size_t c, T value)
    {
        if ( r >= this->_row || c >= this->_column )
        {
            std::cerr << "setElement(): Indices are out of range" << std::endl;
            return false;
        }

        _elem[ this->_column * r + c] = value;
        return true;
    }

    // Operator overloading
    Matrix operator+(const Matrix<T> & B) const
    {
        Matrix<T> MAT_SUM;
        if (this ->_column != B._column || this ->_row != B._row )
        {
            ERROR_INPUT_INPUTPARA;
            std::cout << "This error happened operator+" << std::endl;
            return MAT_SUM;
        }
        else
        {
            MAT_SUM._column = this -> _column;
            MAT_SUM._row = this -> _row;
            MAT_SUM._size = this -> _size;
            MAT_SUM._elem = new T[_size];
            memset(MAT_SUM._elem, 0, MAT_SUM._size * sizeof(T));
            

            for(size_t i = 0; i < this ->_size; i++)
            {
                MAT_SUM._elem[i] = this -> _elem[i] + B._elem[i];
            }
            return MAT_SUM;
        }

    }

    Matrix operator-(const Matrix<T> & B) const
    {
        Matrix<T> MAT_SUB;
        if (this ->_column != B._column || this ->_row != B._row )
        {
            ERROR_INPUT_INPUTPARA;
            std::cout << "This error happened operator-" << std::endl;
            return MAT_SUB;
        }
        else
        {
            MAT_SUB._column = this -> _column;
            MAT_SUB._row = this -> _row;
            MAT_SUB._size = this -> _size;
            MAT_SUB._elem = new T[_size];
            memset(MAT_SUB._elem, 0, MAT_SUB._size * sizeof(T));
            

            for(size_t i = 0; i < this ->_size; i++)
            {
                MAT_SUB._elem[i] = this -> _elem[i] - B._elem[i];
            }
            return MAT_SUB;
        }

    }

    Matrix operator*(const T scalar) const
    {
        Matrix<T> DOT_PRODUCT(this -> _column, this -> _row);

        for(size_t i = 0; i < this ->_size; i++)
        {
            DOT_PRODUCT._elem[i] = this -> _elem[i] * scalar;
        }

        return DOT_PRODUCT;
    }
    
    // friend function parameter list has order!
    friend Matrix<T> operator*(const T scalar, const Matrix<T> & Mat)
    {
        return Mat * scalar;
    }

};




#endif