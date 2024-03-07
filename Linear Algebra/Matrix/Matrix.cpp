#include "Matrix.h"
#include <algorithm> 
#include <vector>
#include <stdexcept>

// Default constructor
// New matrix with 0s
template <class T>
Matrix<T>::Matrix() : rows(0), columns(0) {}

// Constructor with rows and columns
template <class T>
Matrix<T>::Matrix(int rows, int columns) : rows(rows), columns(columns), data(rows * columns) {}

// Constructor with rows, columns, and data
template <class T>
Matrix<T>::Matrix(int rows, int columns, const T* input_data) : rows(rows), columns(columns), data(rows * columns) {
    std::copy(input_data, input_data + rows * columns, data.begin());
}

// Copy constructor
template <class T>
Matrix<T>::Matrix(const Matrix<T>& input_Matrix) : rows(input_Matrix.rows), columns(input_Matrix.columns), data(input_Matrix.data) {}

// Destructor
template <class T>
Matrix<T>::~Matrix() {}

// Resize the matrix
template <class T>
bool Matrix<T>::resize(int nRows, int nColumns) {
    data.resize(nRows * nColumns);
    rows = nRows;
    columns = nColumns;
    return true; 
}

template <class T>
T Matrix<T>::get_element(int row, int column) {
    if(row >= rows || column >= columns || row < 0 || column < 0) {
        throw std::out_of_range("Index out of range");
    }
    return data[row * columns + column];
}

template <class T>
bool Matrix<T>::set_element(int row, int column, T element_value) {
    if(row >= rows || column >= columns || row < 0 || column < 0) {
        return false;
    }
    data[row * columns + column] = element_value;
    return true;
}

template <class T>
int Matrix<T>::get_num_rows() {
    return rows;
}

template <class T>
int Matrix<T>::get_num_cols() {
    return columns;
}

template class Matrix<int>;
template class Matrix<float>;
template class Matrix<double>;
