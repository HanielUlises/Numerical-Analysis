#include "Matrix.h"

// Default constructor
// New matrix with 0s
template <class T>
Matrix<T>::Matrix() {
    rows = 1;
    columns = 1;
    n_elements = 1;
    matrix_data = new T[n_elements];
    matrix_data[0] = 0.0;
}

// Constructor with specified rows and columns
template <class T>
Matrix<T>::Matrix(int rows, int columns) {
    this -> rows = rows;
    this -> columns = columns;
    n_elements = rows * columns;
    matrix_data = new T[n_elements];

    for(int i = 0; i < n_elements; i++){
        matrix_data[i] = 0.0;
    }
}

// Constructor with rows, columns, and data specified
template <class T>
Matrix<T>::Matrix(int rows, int columns, const T* input_data) {
    this -> rows = rows;
    this -> columns = columns;
    n_elements = rows * columns;
    matrix_data = new T[n_elements];

    for(int i = 0; i < n_elements; i++){
        matrix_data[i] = input_data[i];
    }
}

// Copy constructor
template <class T>
Matrix<T>::Matrix(const Matrix<T>& input_Matrix) {
    rows = input_Matrix.rows;
    columns = input_Matrix.columns;
    n_elements = input_Matrix.n_elements;
    matrix_data = new T[n_elements];

    for(int i = 0; i < n_elements; i++){
        matrix_data[i] = input_Matrix.matrix_data[i];
    }
}

// Destructor
template <class T>
Matrix<T>::~Matrix() {
    if(matrix_data != nullptr){
        delete[] matrix_data;
    }
}

template <class T>
int Matrix<T>::sub_to_index(int row, int col) const {
    return row * columns + col; 
}

// Resize the matrix
template <class T>
bool Matrix<T>::resize(int nRows, int nColumns) {
    rows = nRows;
    columns = nColumns;
    n_elements = (rows * columns);
    delete[] matrix_data;
    matrix_data = new T[n_elements];
    if(matrix_data != nullptr){
        for(int i = 0; i < n_elements; i++){
            matrix_data[i] = 0.0;
        }
        return true;
    }else{
        return false;
    }
}

template <class T>
T Matrix<T>::get_element(int row, int column) {
    if (row >= rows || column >= columns || row < 0 || column < 0) {
        throw std::out_of_range("Index out of range");
    }
    return matrix_data[sub_to_index(row, column)];
}


template <class T>
bool Matrix<T>::set_element(int row, int column, T element_value) {
    if (row >= rows || column >= columns || row < 0 || column < 0) {
        return false;
    }
    matrix_data[sub_to_index(row, column)] = element_value;
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
