#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <cmath>
#include <iostream>

class Matrix {
 private:
  // Attributes
  int rows_, cols_;
  double** matrix_;

  // Support functions

  void AllocateMemory();
  void CopyMatrix(const Matrix& other);
  void RemoveMatrix();
  Matrix GetMinor(int rows, int cols) const;

 public:
  Matrix();                            // Default constructor
  Matrix(int rows, int cols);          // Parameterized constructor
  Matrix(const Matrix& other);      // Copy constructor
  Matrix(Matrix&& other) noexcept;  // Move constructor
  ~Matrix();                           // Destructor

  // Getters and Setters

  int GetRows() const noexcept;
  void SetRows(int rows);
  int GetCols() const noexcept;
  void SetCols(int cols);

  // Matrix operations

  // Checks matrices for equality with each other
  bool EqMatrix(const Matrix& other) const;
  // Adds the second matrix to the current one
  void SumMatrix(const Matrix& other);
  // Subtracts another matrix from the current one
  void SubMatrix(const Matrix& other);
  // Multiplies the current matrix by a number
  void MulNumber(const double num);
  // Multiplies the current matrix by the second matrix
  void MulMatrix(const Matrix& other);
  // Creates a new transposed matrix from the current one and returns it
  Matrix Transpose() const;
  // Calculates and returns the determinant of the current matrix
  double Determinant() const;
  // Calculates the algebraic addition matrix of the current one and returns it
  Matrix CalcComplements() const;
  // Calculates and returns the inverse matrix
  Matrix InverseMatrix() const;

  // Operator overloading

  Matrix operator+(const Matrix& other);
  Matrix operator-(const Matrix& other);
  Matrix operator*(const Matrix& other);
  friend Matrix operator*(const Matrix& other, double num);
  friend Matrix operator*(double num, const Matrix& other);
  bool operator==(const Matrix& other);
  Matrix& operator=(const Matrix& other);
  Matrix& operator=(Matrix&& other) noexcept;
  Matrix& operator+=(const Matrix& other);
  Matrix& operator-=(const Matrix& right);
  Matrix& operator*=(const Matrix& right);
  Matrix& operator*=(const double& right);
  double& operator()(int rows, int cols);
  double operator()(int rows, int cols) const;
};

#endif  // SRC_S21_MATRIX_OOP_H_
