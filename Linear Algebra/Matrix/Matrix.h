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


    private:
    int rows, columns;
    std::vector<T> data;
};

#endif // MATRIX_H