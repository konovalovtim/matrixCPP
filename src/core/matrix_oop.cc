#include "matrix_oop.h"

Matrix::Matrix() {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ < 0 || cols_ < 0) {
    throw std::invalid_argument("Arguments less than zero");
  }
  AllocateMemory();
}

Matrix::Matrix(const Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  AllocateMemory();
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) this->matrix_[i][j] = other.matrix_[i][j];
}

Matrix::Matrix(Matrix &&other) noexcept {
  matrix_ = other.matrix_;
  cols_ = other.cols_;
  rows_ = other.rows_;
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

Matrix::~Matrix() { RemoveMatrix(); }

int Matrix::GetRows() const noexcept { return rows_; }

void Matrix::SetRows(int rows) {
  if (rows <= 0 || cols_ <= 0) {
    RemoveMatrix();
    throw std::out_of_range("Incorrect input, different size of matrices");
  }
  Matrix buf(*this);
  RemoveMatrix();
  rows_ = rows;
  cols_ = buf.cols_;
  AllocateMemory();
  int minRows = std::min(rows_, buf.rows_);
  for (int i = 0; i < minRows; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = buf.matrix_[i][j];
    }
  }
}

int Matrix::GetCols() const noexcept { return cols_; }

void Matrix::SetCols(int cols) {
  if (cols <= 0 || rows_ <= 0) {
    RemoveMatrix();
    throw std::out_of_range("Incorrect input, different size of matrices");
  }
  Matrix buf(*this);
  RemoveMatrix();
  rows_ = buf.rows_;
  cols_ = cols;
  AllocateMemory();
  int minCols = std::min(cols, buf.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < minCols; j++) {
      matrix_[i][j] = buf.matrix_[i][j];
    }
  }
}

bool Matrix::EqMatrix(const Matrix &other) const {
  bool result = false;
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    result = true;
    for (int i = 0; i < this->rows_ && result; i++)
      for (int j = 0; j < this->cols_ && result; j++)
        if (fabs(this->matrix_[i][j] - other.matrix_[i][j]) > 1e-7)
          result = false;
  }
  return result;
}

void Matrix::SumMatrix(const Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Incorrect input, different size of matrices");
  }
  for (int i = 0; i < this->rows_; i++)
    for (int j = 0; j < this->cols_; j++)
      this->matrix_[i][j] += other.matrix_[i][j];
}

void Matrix::SubMatrix(const Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Incorrect input, different size of matrices");
  }
  for (int i = 0; i < this->rows_; i++)
    for (int j = 0; j < this->cols_; j++)
      this->matrix_[i][j] -= other.matrix_[i][j];
}

void Matrix::MulNumber(const double num) {
  for (int i = 0; i < this->rows_; i++)
    for (int j = 0; j < this->cols_; j++) this->matrix_[i][j] *= num;
}

void Matrix::MulMatrix(const Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument("Incorrect input, different size of matrices");
  }
  Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        result.matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  RemoveMatrix();
  *this = std::move(result);
}

Matrix Matrix::Transpose() const {
  Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result(j, i) = (*this)(i, j);
    }
  }
  return result;
}

double Matrix::Determinant() const {
  if (cols_ != rows_) throw std::out_of_range("The matrix isn't square!");
  double result = 0;
  if (rows_ == 1) {
    result = matrix_[0][0];
  } else if (rows_ == 2) {
    result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    for (int i = 0; i < cols_; i++) {
      Matrix minor = this->GetMinor(0, i);
      double buff = minor.Determinant();
      double newMinor = pow(-1, i) * matrix_[0][i] * buff;
      result += newMinor;
    }
  }
  return result;
}

Matrix Matrix::CalcComplements() const {
  if (cols_ != rows_) throw std::out_of_range("The matrix isn't square!");
  Matrix result = Matrix(rows_, cols_);
  for (int i = 0; i < result.rows_; i++)
    for (int j = 0; j < result.cols_; j++) {
      Matrix minor = this->GetMinor(i, j);
      double determinant = minor.Determinant();
      determinant *= pow(-1, i + j);
      result.matrix_[i][j] = determinant;
    }
  return result;
}

Matrix Matrix::InverseMatrix() const {
  double det = this->Determinant();
  if (det == 0)
    throw std::invalid_argument("Incorrect input, matrix determinant is zero");
  Matrix calc = this->CalcComplements();
  Matrix result = calc.Transpose();
  result.MulNumber(1.0 / det);
  return result;
}

Matrix Matrix::operator+(const Matrix &other) {
  Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

Matrix Matrix::operator-(const Matrix &other) {
  Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

Matrix Matrix::operator*(const Matrix &other) {
  Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

Matrix operator*(double num, const Matrix &other) {
  Matrix result(other);
  result.MulNumber(num);
  return result;
}

Matrix operator*(const Matrix &other, double num) {
  Matrix result(other);
  result.MulNumber(num);
  return result;
}

bool Matrix::operator==(const Matrix &other) { return EqMatrix(other); }

Matrix &Matrix::operator+=(const Matrix &other) {
  this->SumMatrix(other);
  return *this;
}

Matrix &Matrix::operator-=(const Matrix &other) {
  this->SubMatrix(other);
  return *this;
}

Matrix &Matrix::operator*=(const Matrix &other) {
  this->MulMatrix(other);
  return *this;
}

Matrix &Matrix::operator*=(const double &other) {
  this->MulNumber(other);
  return *this;
}

double &Matrix::operator()(int rows, int cols) {
  if (rows < 0 || cols < 0 || rows >= rows_ || cols >= cols_)
    throw std::out_of_range("Index is outside the matrix");
  return matrix_[rows][cols];
}

double Matrix::operator()(int rows, int cols) const {
  if (rows < 0 || cols < 0 || rows >= rows_ || cols >= cols_)
    throw std::out_of_range("Index is outside the matrix");
  return matrix_[rows][cols];
}

Matrix &Matrix::operator=(const Matrix &other) {
  if (this != &other) {
    RemoveMatrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    AllocateMemory();
    CopyMatrix(other);
  }
  return *this;
}

Matrix &Matrix::operator=(Matrix &&other) noexcept {
  if (this != &other) {
    RemoveMatrix();
    matrix_ = other.matrix_;
    cols_ = other.cols_;
    rows_ = other.rows_;
    other.matrix_ = nullptr;
    other.rows_ = 0;
    other.cols_ = 0;
  }
  return *this;
}

Matrix Matrix::GetMinor(int rows, int cols) const {
  Matrix result = Matrix(rows_ - 1, cols_ - 1);
  int n = 0;
  for (int i = 0; i < rows_; i++) {
    if (i != rows) {
      int m = 0;
      for (int j = 0; j < cols_; j++)
        if (j != cols) result.matrix_[n][m++] = matrix_[i][j];
      n++;
    }
  }
  return result;
}

void Matrix::AllocateMemory() {
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) matrix_[i] = new double[cols_]{0};
}

void Matrix::CopyMatrix(const Matrix &other) {
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] = other.matrix_[i][j];
}

void Matrix::RemoveMatrix() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}
