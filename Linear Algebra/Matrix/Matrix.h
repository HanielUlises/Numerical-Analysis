#ifndef MATRIX_H
#define MATRIX_H

#include <algorithm> 
#include <vector>
#include <stdexcept>

// Ontological definition
// I've always wanted to write this into a .h file (sob)
template <class T>
class Matrix{
    public:
    // Constructors
    Matrix();
    Matrix(int rows, int columns);
    Matrix(int rows, int columns, const T* input_data);
    Matrix(const Matrix<T>& input_Matrix);

    ~Matrix();
    // Succesful or not succesful resizing of matrix
    bool resize (int nRows, int nColumns);
    
    // Access methods
    T get_element (int row, int column);
    bool set_element (int row, int column, T element_value);
    int get_num_rows();
    int get_num_cols();

    // Operations
    // Equality
    bool operator== (const Matrix<T> & rhs)

    // Sum of matrices
    template <class U> friend Matrix<U> operator+ (const Matrix<U>& lhs, cosnt Matrix<U>& rhs);
    template <class U> friend Matrix<U> operator+ (const U& lhs, const Matrix<U>& rhs);
    tempalte <class U> friend Matrix<U> operator+ (const Matrix<U>& lhs, const U& rhs);

    // Difference of matrices
    template <class U> friend Matrix<U> operator- (const Matrix<U>& lhs, cosnt Matrix<U>& rhs);
    template <class U> friend Matrix<U> operator- (const U& lhs, const Matrix<U>& rhs);
    tempalte <class U> friend Matrix<U> operator- (const Matrix<U>& lhs, const U& rhs);

    // Product of matrices
    template <class U> friend Matrix<U> operator* (const Matrix<U>& lhs, cosnt Matrix<U>& rhs);
    template <class U> friend Matrix<U> operator* (const U& lhs, const Matrix<U>& rhs);
    tempalte <class U> friend Matrix<U> operator* (const Matrix<U>& lhs, const U& rhs);

    private:
    int sub_to_index(int row, int col) const;

    private:
    int rows, columns, n_elements;
    T* matrix_data;
};

#endif // MATRIX_H