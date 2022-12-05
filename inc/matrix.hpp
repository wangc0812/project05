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
        _row = 0;
        _column = 0;
        _size = 0;
        _elem = NULL;
        std::cout << "default constructor used" << std::endl; 
    }

    // this constructor is to construct a full zero matrix with given size
    Matrix(size_t r, size_t c) : _row(r), _column(c)
    {
        if (r == 0 || c == 0 )
        {
            ERROR_INPUT_INPUTPARA;
            std::cerr << "This error happened in constructor" << std::endl;
            return;
        }
        else
        {
            _size = _row * _column;
            _elem = new T[_size];

            if (_elem == NULL)
            {
                std::cerr << "Matrix(size_t r, size_t c) : failed to allocate memory for matrix data" << std::endl;
                delete[] _elem;
                _elem = NULL;
                return;
            }
            
            memset(_elem, 0, _size * sizeof(T));
            std::cout << "constructor used" << std::endl;

        }

    }

    Matrix(size_t r, size_t c, T * data) : _row(r), _column(c)
    {
        if (r == 0 || c == 0 )
        {
            ERROR_INPUT_INPUTPARA;
            std::cerr << "This error happened in constructor" << std::endl;
            return;
        }

        if (data == NULL)
        {
            std::cerr << "input data invalid" << std::endl;
            return;
        }
        
        this -> _size = 0;
        this -> _elem = NULL;

        size_t size = this -> _column * this -> _row;
        create(size, data);

        std::cout << "constructor with data used" << std::endl;

    }

    Matrix(const Matrix<T> & rhs)
    {
    
        if(rhs._elem == NULL)
        {
         std::cerr << "Matrix(const Matrix<T> & rhs) : rhs data invalid" << std::endl; 
         return;  
        }
        
        this -> _size = 0;
        this -> _elem = NULL;

        create(rhs._size, rhs._elem);
        this -> _column = rhs._column;
        this -> _row = rhs._row;

        std::cout << "copy constructor used" << std::endl; 

    }
    
    bool create(size_t size,  const T * data)
    {
        release();

        if (size == 0)
        {
            std::cerr << "ERROR: matrix size is zero" << std::endl;
            return false;
        }

        if(data == NULL)
        {
            std::cerr << "input data invalid" << std::endl;
            return false;
        }
        
        this -> _size = size;

        if(this -> _size != 0)
        {
            this -> _elem = new T[this -> _size];
        }

        if (_elem == NULL)
        {
            std::cerr << "failed to allocate memory for matrix data" << std::endl;
            delete[] _elem;
            _elem = NULL;
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
        release();
        std::cout << "deconstructor used" << std::endl;
            
    }

    // Print Matrix or Elems
    void printMatrix() const
    {
        if(this->_elem != NULL)
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
            std::cerr << "This error happened in printMatrix()" << std::endl;
        }

    }

    T getElement(size_t r, size_t c) const
    {
        if ( r >= this->_row || c >= this->_column )
        {
            std::cerr << "getElement(): Indices are out of range" << std::endl;
            return 1;
        }
        if (this -> _elem == NULL)
        {
            std::cerr << "getElement(): input matrix data invalid" << std::endl;
            return 1;
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

        if (this -> _elem == NULL)
        {
            std::cerr << "setElement(): input matrix data invalid" << std::endl;
            return false;
        }
        
        _elem[ this->_column * r + c] = value;
        return true;
    }

    // Operator overloading
    Matrix<T> operator+(const Matrix<T> & B) const
    {
        if (B._elem == NULL || this -> _elem == NULL)
        {   
            std::cerr << "matrix data invalid" << std::endl;
            std::cerr << "This error happened operator+" << std::endl;
            return *this;
        }
        
        if (this ->_column != B._column || this ->_row != B._row )
        {
            ERROR_INPUT_INPUTPARA;
            std::cerr << "This error happened operator+" << std::endl;
            return *this;
        }
        
        Matrix<T> MAT_SUM(this -> _column, this -> _row);
            
        for(size_t i = 0; i < this ->_size; i++)
        {
            MAT_SUM._elem[i] = this -> _elem[i] + B._elem[i];
        }

        return MAT_SUM;
  

    }

    Matrix<T> operator-(const Matrix<T> & B) const
    {
        if (B._elem == NULL || this -> _elem == NULL)
        {   
            std::cerr << "matrix data invalid" << std::endl;
            std::cerr << "This error happened operator-" << std::endl;
            return *this;
        }

        if (this ->_column != B._column || this ->_row != B._row )
        {
            ERROR_INPUT_INPUTPARA;
            std::cerr << "This error happened operator-" << std::endl;
            return *this;
        }

        Matrix<T> MAT_SUB(this -> _column, this -> _row);

        for(size_t i = 0; i < this ->_size; i++)
        {
            MAT_SUB._elem[i] = this -> _elem[i] - B._elem[i];
        }
        return MAT_SUB;
        

    }

    Matrix operator*(const T scalar) const
    {
        if (this -> _elem == NULL)
        {   
            std::cerr << "matrix data invalid" << std::endl;
            std::cerr << "This error happened in Matrix operator*(const T scalar)" << std::endl;
            return *this;
        }
        
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