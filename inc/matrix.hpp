#ifndef  __MATRIX_H__
#define  __MATRIX_H__

#include <iostream>
#include "define.h"
#include <string.h>
#include <iomanip>

// struct MatrixValue define
template <typename T>
struct MatrixValue{
        int *refCount;
        size_t _row, _column, _size;
        T * _elem;
        MatrixValue();
        MatrixValue(size_t r, size_t c);
        MatrixValue(size_t r, size_t c, T * data);
        bool create(size_t size,  const T * data);
        bool release();
        ~MatrixValue();
};

// Class Matrix define
template <typename T>
class Matrix
{    
private:

    MatrixValue<T> *value = new MatrixValue<T>();

public:
    // this constructor is to construct a full zero matrix with given size
    Matrix(size_t r, size_t c): value(new MatrixValue<T>(r,c)){}
    Matrix(size_t r, size_t c, T * data): value(new MatrixValue<T>(r,c, data)){}
    Matrix(const Matrix<T> &rhs);
    Matrix(){};
    ~Matrix();

    void printMatrix() const;
    
    T getElement(size_t r, size_t c) const;
    bool setElement(size_t r, size_t c, T inValue);
    size_t shape(int flag) const;
    
    Matrix<T> ROI(size_t startX, size_t startY, size_t endX, size_t endY) const;
    Matrix<T>& operator=(const Matrix<T> &B);
    Matrix<T> operator+(const Matrix<T> &B) const;
    Matrix<T> operator-(const Matrix<T> &B) const;
    Matrix<T> operator*(const T scalar) const;
    Matrix<T> operator*(const Matrix<T> &B) const;
    friend Matrix<T> matmul(const Matrix<T> &A, const Matrix<T> &B)
    {
        if (A.value->_elem == NULL || B.value->_elem == NULL)
        {
            std::cerr << "matrix data invalid" << std::endl;
            std::cerr <<"this error happened in matmul"<< std::endl;
            exit(-1);
        }

        if (A.value->_column != B.value->_row)
        {
            ERROR_SIZE_MATCH;
            std::cerr <<"this error happened in matmul"<< std::endl;
            exit(-1);
        }

        size_t i, j, k;
        Matrix<T> MAT_PRO(A.value->_row, B.value->_column);

        for(i = 0; i < A.value->_row; i++)
        {
            for(j = 0; j < B.value->_column; j++)
            {
                for(k = 0; k < A.value->_row; k++)
                {
                    MAT_PRO.value->_elem[j + i * B.value->_column] += A.value->_elem[(i * A.value->_column) + k] * B.value->_elem[(k * B.value->_column) + j];
                }
            }
        }

        return  MAT_PRO;
    }
    friend Matrix<T> operator*(const T scalar, const Matrix<T> &Mat){
        return Mat * scalar;
    }
};

template<typename T>
Matrix<T> Matrix<T>::ROI(size_t startX, size_t startY, size_t endX, size_t endY) const
{
    if(value->_elem == NULL)
    {
        std::cerr << "Matrix<T>& ROI(const Matrix<T> BigMatrix, size_t startX, size_t startY, size_t endX, size_t end) : rhs data invalid" << std::endl; 
        exit(-1); 
    }
    if(startX < 0 || startY < 0 || endX < 0 || endY < 0 || startX > value->_column || endX > value->_column || startY > value->_row || endY > value->_row)
    {
        std::cerr<< "ROI: input coord out of range" << std::endl;
        exit(-1);
    }
    size_t row = endX - startX + 1;
    size_t column = endY - startY + 1;
    size_t size = row * column;
    Matrix<T> ROIMat(row, column);

    size_t elem_count = 0;
    for(size_t i=0; i < row; i++){
        for(size_t j=0; j < column; j++){
            ROIMat.value->_elem[elem_count] = value->_elem[(startX + i) * value->_column + startY + j];
            ++elem_count;
        }
    }
    ROIMat.value->refCount = this->value->refCount;
    ++ *value->refCount;
    return ROIMat;

}

template<typename T>
size_t Matrix<T>::shape(int flag) const
{
    if (flag == 0)
        {
            return value->_row;
        }

        if(flag == 1)
        {
            return value->_column;
        }
        
        std::cerr<< "flag needed to be 1 or 0"<<std::endl;
        std::cerr<< "invalid input" <<std::endl;
        exit(-1);
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &B) const
{
    Matrix<T> PRO = matmul(*this, B);
    return PRO;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const T scalar) const
{
    if (value->_elem == NULL)
        {   
            std::cerr << "matrix data invalid" << std::endl;
            std::cerr << "This error happened in Matrix operator*(const T scalar)" << std::endl;
            exit(-1);
        }
        
        Matrix<T> DOT_PRODUCT(value->_row, value->_column);

        for(size_t i = 0; i < value->_size; i++)
        {
            DOT_PRODUCT.value->_elem[i] = value->_elem[i] * scalar;
        }

        return DOT_PRODUCT;
}
template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &B) const
{
    if (B.value->_elem == NULL || value-> _elem == NULL)
        {   
            std::cerr << "matrix data invalid" << std::endl;
            std::cerr << "This error happened operator+" << std::endl;
            exit(-1);
        }
        
        if (value->_column != B.value->_column || value->_row != B.value->_row )
        {
            ERROR_INPUT_INPUTPARA;
            std::cerr << "This error happened operator+" << std::endl;
            exit(-1);
        }
        
        Matrix<T> MAT_SUM(value->_row, value->_column);
            
        for(size_t i = 0; i < value->_size; i++)
        {
            MAT_SUM.value->_elem[i] = value->_elem[i] - B.value->_elem[i];
        }

        return MAT_SUM;
}
template<typename T>
  Matrix<T> Matrix<T>::operator+(const Matrix<T> &B) const
  {
    if (B.value->_elem == NULL || value-> _elem == NULL)
        {   
            std::cerr << "matrix data invalid" << std::endl;
            std::cerr << "This error happened operator+" << std::endl;
            exit(-1);
        }
        
        if (value->_column != B.value->_column || value->_row != B.value->_row )
        {
            ERROR_INPUT_INPUTPARA;
            std::cerr << "This error happened operator+" << std::endl;
            exit(-1);
        }
        
        Matrix<T> MAT_SUM(value->_row, value->_column);
            
        for(size_t i = 0; i < value->_size; i++)
        {
            MAT_SUM.value->_elem[i] = value->_elem[i] + B.value->_elem[i];
        }

        return MAT_SUM;
  }

// copy constructor
template<typename T>
Matrix<T>::Matrix(const Matrix<T> &rhs){

    if(rhs.value->_elem == NULL)
        {
         std::cerr << "Matrix(const Matrix<T> & rhs) : rhs data invalid" << std::endl; 
         exit(-1);  
        }
        value -> _size = 0;
        value -> _elem = NULL;  
        value->create(rhs.value->_size, rhs.value->_elem);
        this->value -> _column = rhs.value->_column;
        this->value -> _row = rhs.value->_row;
        this->value->refCount = rhs.value->refCount;

        std::cout<<"copy constructor refCount:"<< *value->refCount << std::endl;
        ++ *value->refCount;
        std::cout<<"copy constructor refCount:"<< *value->refCount << std::endl;

        std::cout << "copy constructor used" << std::endl; 
}

// overloading operator = 
template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T> &B){
    if(this == &B)
    {
        return * this;
    }

    if (B.value->_elem == NULL)
    {   
        std::cerr << "matrix data invalid" << std::endl;
        std::cerr << "This error happened operator=" << std::endl;
        exit(-1);
    }
    
    value->_row = B.value->_row, value->_column = B.value->_column;
    this->value->refCount = B.value->refCount;
    bool flag = value->create(B.value->_size, B.value->_elem);
    std::cout<<flag<<std::endl;
    if(flag == false)
    {
        std::cerr << "create() fail" << std::endl;
        std::cerr << "This error happened operator=" << std::endl;
        exit(-1);
    }
    ++ *value->refCount;
    return * this;
}

template<typename T>
T Matrix<T>::getElement(size_t r, size_t c) const
{
    if ( r >= this->value->_row || c >= this->value->_column )
        {
            std::cerr << "getElement(): Indices are out of range" << std::endl;
            exit(-1);
        }
        if (this -> value->_elem == NULL)
        {
            std::cerr << "getElement(): input matrix data invalid" << std::endl;
            exit(-1);
        }

        return value->_elem[ this->value->_column * r + c];
}

template<typename T>
bool Matrix<T>::setElement(size_t r, size_t c, T inValue)
{
    if ( r >= this->value->_row || c >= this->value->_column )
        {
            std::cerr << "setElement(): Indices are out of range" << std::endl;
            return false;
        }

        if (this ->value->_elem == NULL)
        {
            std::cerr << "setElement(): input matrix data invalid" << std::endl;
            return false;
        }
        
        value->_elem[ this->value->_column * r + c] = inValue;
        return true;
}
// This function is to release the matrix data memory
template<typename T>
bool MatrixValue<T>::release()
{

    if(_elem != NULL)
    {
        delete [] _elem;
        _elem = NULL;
    }

    return true;
}

template<typename T>
bool MatrixValue<T>::create(size_t size,  const T * data)
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
    
    _size = size;

    if(_size != 0)
    {
        _elem = new T[_size];
    }

    if (_elem == NULL)
    {
        std::cerr << "failed to allocate memory for matrix data" << std::endl;
        delete[] _elem;
        _elem = NULL;
        return false;
    }

    memcpy(_elem, data, _size);

    return true;
}
template<typename T>
MatrixValue<T>::MatrixValue():refCount(new int(1)){
    _row = 0, _column = 0;
}
template<typename T>
MatrixValue<T>::MatrixValue(size_t r, size_t c, T * data):refCount(new int(1)){
    if (r == 0 || c == 0 )
        {
            ERROR_INPUT_INPUTPARA;
            std::cerr << "This error happened in constructor" << std::endl;
            exit(-1);
        }

        if (data == NULL)
        {
            std::cerr << "input data invalid" << std::endl;
            exit(-1);
        }
        _row = r, _column = c;
        _size = 0;
        _elem = NULL;

        size_t size = _column * _row;
        bool flag = create(size, data);

        if(flag == false)
        {
            std::cerr << "create() fail" << std::endl;
            exit(-1);
        }

        std::cout << "constructor with data used" << std::endl;
}

// Matrix destructor
template<typename T>
Matrix<T>::~Matrix(){if(-- *value->refCount==0) delete value;}

template<typename T>
MatrixValue<T>::~MatrixValue() {delete[] _elem;};

template<typename T>
MatrixValue<T>::MatrixValue(size_t r, size_t c):refCount(new int(1)){
    if (r == 0 || c == 0 )
    {
        ERROR_INPUT_INPUTPARA;
        std::cerr << "This error happened in constructor" << std::endl;
        exit(-1);
    }
    else
    {
        _row = r, _column=c;
        _size = _row * _column;
        _elem = new T[_size];

        if (_elem == NULL)
        {
            std::cerr << "Matrix(size_t r, size_t c) : failed to allocate memory for matrix data" << std::endl;
            delete[] _elem;
            _elem = NULL;
            exit(-1);
        }
        if (typeid(T) == typeid(unsigned char)){
            unsigned char a = '0';
            memset(_elem, a, _size * sizeof(T));
        }
        else memset(_elem, 0, _size * sizeof(T));
        std::cout << "constructor used" << std::endl;

    };
};

template<typename T>
void Matrix<T>::printMatrix() const{
    if(this->value->_elem != NULL)
            {
                std::cout<< "---------------Matrix Print Start----------------" <<std::endl;
                
                size_t i, j;
                for (i = 0; i < value->_row; i++) 
                {
                    for (j = 0; j < value->_column; j++)
                    {
                        std::cout << this->value->_elem[i * (this->value->_column) + j]<<" " ;
                    }

                std::cout << std::endl;
                }
                std::cout<<"refcount = " << *this->value->refCount<<std::endl;

                std::cout<< "---------------Matrix Print End----------------" <<std::endl;
            }
        else
            {
                ERROR_INPUT_POINTER;
                std::cerr << "This error happened in printMatrix()" << std::endl;
            }
}
#endif