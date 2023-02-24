#include <gtest/gtest.h>

#include "../core/matrix_oop.h"

TEST(test, defaultConstructor) {
  Matrix basic;
  EXPECT_EQ(basic.GetRows(), 0);
  EXPECT_EQ(basic.GetCols(), 0);
}

TEST(test, parameterizedConstructor) {
  Matrix basic(2, 3);
  EXPECT_EQ(basic.GetRows(), 2);
  EXPECT_EQ(basic.GetCols(), 3);
}

TEST(test, copyConstructor) {
  Matrix basic(2, 3);
  Matrix result(basic);
  EXPECT_EQ(result.GetRows(), 2);
  EXPECT_EQ(result.GetCols(), 3);
  EXPECT_EQ(basic == result, true);
}

TEST(test, moveConstructor) {
  Matrix basic(2, 3);
  Matrix result(std::move(basic));
  EXPECT_EQ(result.GetRows(), 2);
  EXPECT_EQ(result.GetCols(), 3);
  EXPECT_EQ(basic.GetRows(), 0);
  EXPECT_EQ(basic.GetCols(), 0);
}

TEST(test, brakets) {
  Matrix basic(2, 3);
  basic(1, 1) = 3;
  EXPECT_EQ(basic(1, 1), 3);
}

TEST(test, zeroMatrix) {
  Matrix basic;
  EXPECT_EQ(basic.GetRows(), 0);
  EXPECT_EQ(basic.GetCols(), 0);
}

TEST(test, moveConst) {
  Matrix basic(2, 3);
  Matrix basic2 = std::move(basic);
  EXPECT_EQ(basic.GetRows(), 0);
  EXPECT_EQ(basic.GetCols(), 0);
  EXPECT_EQ(basic2.GetRows(), 2);
  EXPECT_EQ(basic2.GetCols(), 3);
}

TEST(test, determinant) {
  Matrix basic(4, 4);
  basic(0, 0) = 9;
  basic(0, 1) = 2;
  basic(0, 2) = 2;
  basic(0, 3) = 4;

  basic(1, 0) = 3;
  basic(1, 1) = 4;
  basic(1, 2) = 4;
  basic(1, 3) = 4;

  basic(2, 0) = 4;
  basic(2, 1) = 4;
  basic(2, 2) = 9;
  basic(2, 3) = 9;

  basic(3, 0) = 1;
  basic(3, 1) = 1;
  basic(3, 2) = 5;
  basic(3, 3) = 1;
  EXPECT_DOUBLE_EQ(basic.Determinant(), -578);
}

TEST(test, determinant2) {
  Matrix basic(1, 1);
  basic(0, 0) = 10;
  EXPECT_DOUBLE_EQ(basic.Determinant(), 10);
}

TEST(test, determinant3) {
  Matrix basic(2, 2);
  basic(0, 0) = 1.1;
  basic(0, 1) = 3.5;

  basic(1, 0) = -2;
  basic(1, 1) = 4;
  EXPECT_DOUBLE_EQ(basic.Determinant(), 11.4);
}

TEST(test, inverseMatrix) {
  Matrix basic(3, 3);

  basic(0, 0) = 4;
  basic(0, 1) = -2;
  basic(0, 2) = 1;

  basic(1, 0) = 1;
  basic(1, 1) = 6;
  basic(1, 2) = -2;

  basic(2, 0) = 1;
  basic(2, 1) = 0;
  basic(2, 2) = 0;

  basic = basic.InverseMatrix();

  EXPECT_EQ(basic(0, 1), 0);
  EXPECT_EQ(basic(0, 2), 1);

  EXPECT_EQ(basic(1, 0), 1);
  EXPECT_EQ(basic(2, 0), 3);

  EXPECT_EQ(basic(2, 1), 1);
  EXPECT_EQ(basic(2, 2), -13);
}

TEST(test, inverseMatrix2) {
  Matrix basic(3, 3);

  basic(0, 0) = 2;
  basic(0, 1) = 2;
  basic(0, 2) = 123;

  basic(1, 0) = 12;
  basic(1, 1) = 6;
  basic(1, 2) = 5;

  basic(2, 0) = 1;
  basic(2, 1) = 2;
  basic(2, 2) = 8;

  basic = basic.InverseMatrix();

  EXPECT_DOUBLE_EQ(basic(0, 1), 0.10910815939278938);
  EXPECT_DOUBLE_EQ(basic(0, 2), -0.34535104364326374);

  EXPECT_DOUBLE_EQ(basic(1, 0), -0.043168880455407968);
  EXPECT_DOUBLE_EQ(basic(2, 0), 0.0085388994307400382);

  EXPECT_DOUBLE_EQ(basic(2, 1), -0.00094876660341555979);
  EXPECT_DOUBLE_EQ(basic(2, 2), -0.0056925996204933585);
}

TEST(test, transpose) {
  Matrix result(2, 2);

  result(0, 0) = 1;
  result(0, 1) = 2;
  result(1, 0) = 4;
  result(1, 1) = 3;
  result = result.Transpose();

  EXPECT_EQ(result(0, 0), 1);
  EXPECT_EQ(result(0, 1), 4);
  EXPECT_EQ(result(1, 0), 2);
  EXPECT_EQ(result(1, 1), 3);
}

TEST(test, set) {
  Matrix basic(2, 3);
  basic(1, 1) = 2.2;
  EXPECT_EQ(basic(1, 1), 2.2);
  EXPECT_EQ(basic.GetRows(), 2);
  EXPECT_EQ(basic.GetCols(), 3);
  basic.SetRows(4);
  basic.SetCols(3);
  basic(3, 2) = 1.2;
  EXPECT_EQ(basic(1, 1), 2.2);
  EXPECT_EQ(basic(3, 2), 1.2);
  EXPECT_EQ(basic.GetRows(), 4);
  EXPECT_EQ(basic.GetCols(), 3);
}

TEST(test, copy) {
  Matrix a(2, 2);
  Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  a = b;
  EXPECT_DOUBLE_EQ(a(1, 1), 2.2);
}

TEST(test, plus) {
  Matrix a(2, 2);
  Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  Matrix result = a + b;
  EXPECT_DOUBLE_EQ(result(1, 1), 3.3);
}

TEST(test, plus2) {
  Matrix a(2, 2);
  Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  a += b;
  EXPECT_DOUBLE_EQ(a(1, 1), 3.3);
}

TEST(test, plus3) {
  Matrix a(2, 2);
  Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  a.SumMatrix(b);
  EXPECT_DOUBLE_EQ(a(1, 1), 3.3);
}

TEST(test, minus) {
  Matrix a(2, 2);
  Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  Matrix result = a - b;
  EXPECT_DOUBLE_EQ(result(1, 1), -1.1);
}

TEST(test, minus2) {
  Matrix a(2, 2);
  Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  a -= b;
  EXPECT_DOUBLE_EQ(a(1, 1), -1.1);
}

TEST(test, minus3) {
  Matrix a(2, 2);
  Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  a.SubMatrix(b);
  EXPECT_DOUBLE_EQ(a(1, 1), -1.1);
}

TEST(test, multMatrixNum) {
  Matrix a(3, 2);
  a(1, 1) = 1.1;
  Matrix result = a * 2;
  EXPECT_DOUBLE_EQ(result(1, 1), 2.2);
}

TEST(test, multMatrixNum2) {
  Matrix a(3, 2);
  a(1, 1) = 1.1;
  a *= 2;
  EXPECT_DOUBLE_EQ(a(1, 1), 2.2);
}

TEST(test, multMatrixNum3) {
  Matrix a(3, 2);
  a(1, 1) = 1.1;
  a.MulNumber(2);
  EXPECT_DOUBLE_EQ(a(1, 1), 2.2);
}

TEST(test, multMatrixNum4) {
  Matrix a(3, 2);
  a.MulNumber(NAN);
  EXPECT_EQ(std::isnan(a(1, 1)), 1);
  EXPECT_EQ(std::isnan(a(2, 1)), 1);
  EXPECT_EQ(std::isnan(a(1, 0)), 1);
}

TEST(test, equal) {
  Matrix a(2, 3);
  Matrix b(2, 2);
  EXPECT_EQ(a == b, false);
  b.SetRows(2);
  b.SetCols(3);
  a(1, 1) = 1.3;
  b(1, 1) = 1.3;
  EXPECT_EQ(a == b, true);
  b(1, 2) = 1.3;
  EXPECT_EQ(a == b, false);
}

TEST(test, equal2) {
  Matrix a(2, 2);
  Matrix b(2, 2);
  EXPECT_EQ(a == b, true);
  a(1, 1) = 1.3;
  EXPECT_EQ(a == b, false);
  b(1, 1) = 1.3;
  EXPECT_EQ(a == b, true);
}

TEST(test, multMatrix) {
  Matrix a(3, 2);
  Matrix b(2, 3);
  a(1, 1) = 1.1;
  b(1, 1) = 2;
  Matrix result = a * b;
  EXPECT_DOUBLE_EQ(result(1, 1), 2.2);
}

TEST(test, multMatrix2) {
  Matrix a(3, 2);
  Matrix b(2, 3);
  a(1, 1) = 1.1;
  b(1, 1) = 2;
  a *= b;
  EXPECT_DOUBLE_EQ(a(1, 1), 2.2);
}

TEST(test, multMatrix3) {
  Matrix a(3, 2);
  Matrix b(2, 3);
  a(1, 1) = 1.1;
  b(1, 1) = 2;
  a.MulMatrix(b);
  EXPECT_DOUBLE_EQ(a(1, 1), 2.2);
}

TEST(test, multMatrix4) {
  Matrix b(2, 3);
  b(1, 1) = 2;
  Matrix result = 2 * b;
  EXPECT_DOUBLE_EQ(result(1, 1), 4);
}

TEST(test, multMatrixTotal) {
  Matrix a(3, 2);
  Matrix b(2, 4);
  Matrix res(3, 4);

  for (int i = 0, value = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetCols(); j++) a(i, j) = value++;

  for (int i = 0, value = 0; i < b.GetRows(); i++)
    for (int j = 0; j < b.GetCols(); j++) b(i, j) = value++;

  res(0, 0) = 4, res(0, 1) = 5, res(0, 2) = 6, res(0, 3) = 7;
  res(1, 0) = 12, res(1, 1) = 17, res(1, 2) = 22, res(1, 3) = 27;
  res(2, 0) = 20, res(2, 1) = 29, res(2, 2) = 38, res(2, 3) = 47;

  Matrix answer = a * b;
  EXPECT_TRUE(res == answer);
}

TEST(test, calcComplements) {
  Matrix result(2, 2);
  Matrix another(2, 2);

  result(0, 0) = 1;
  result(0, 1) = 2;
  result(1, 0) = 4;
  result(1, 1) = 3;

  another(0, 0) = 1;
  another(0, 1) = 2;
  another(1, 0) = 13;
  another(1, 1) = 7;

  result -= another * result;
  result = result.CalcComplements();

  EXPECT_EQ(result(0, 0), -44);
  EXPECT_EQ(result(0, 1), 37);
  EXPECT_EQ(result(1, 0), 6);
  EXPECT_EQ(result(1, 1), -8);
}

TEST(exception, default_constructor_Exception) {
  EXPECT_ANY_THROW(Matrix exception(1, 0));
}

TEST(exception, parameterized_constructor_Exception) {
  EXPECT_ANY_THROW(Matrix exception(0, -2));
}

TEST(exception, brakets_Exception) {
  Matrix exception(2, 3);
  EXPECT_ANY_THROW(exception(1, 5));
}

TEST(exception, brakets_Exception2) {
  Matrix exception(2, 3);
  EXPECT_ANY_THROW(exception(1, 5));
}

TEST(exception, braket_Exception2) {
  const Matrix exception(1, 1);
  EXPECT_ANY_THROW(exception(5, 4));
}

TEST(exception, plus_Exception) {
  Matrix a(2, 3);
  Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(Matrix result = a + b);
}

TEST(exception, plus_Exception2) {
  Matrix a(2, 3);
  Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a += b);
}

TEST(exception, plus_Exception3) {
  Matrix a(2, 3);
  Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a.SumMatrix(b));
}

TEST(exception, minus_Exception) {
  Matrix a(2, 3);
  Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(Matrix result = a + b);
}

TEST(exception, minus_Exception2) {
  Matrix a(2, 3);
  Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a -= b);
}

TEST(exception, minus_Exception3) {
  Matrix a(2, 3);
  Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a.SubMatrix(b));
}

TEST(exception, minus_Exception4) {
  Matrix a(2, 3);
  Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a - b);
}

TEST(exception, mult_Matrix_Exception) {
  Matrix a(2, 3);
  Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(Matrix result = a * b);
}

TEST(exception, mult_Matrix_Exception2) {
  Matrix a(2, 3);
  Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a *= b);
}

TEST(exception, mult_Matrix_Exception3) {
  Matrix a(2, 3);
  Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a.MulMatrix(b));
}

TEST(exception, determinantException) {
  Matrix exception(4, 3);
  EXPECT_ANY_THROW(exception.Determinant());
}

TEST(exception, inverse_matrixException) {
  Matrix exception(3, 3);
  exception(0, 0) = 1;
  exception(0, 1) = 1;
  exception(0, 2) = 3;
  exception(1, 0) = 4;
  exception(1, 1) = 4;
  exception(1, 2) = 6;
  exception(2, 0) = 4;
  exception(2, 1) = 4;
  exception(2, 2) = 9;
  EXPECT_EQ(exception.Determinant(), 0);
  EXPECT_ANY_THROW(exception.InverseMatrix());
}

TEST(exception, inverse_matrixException2) {
  Matrix exception(3, 3);
  exception(0, 0) = 1;
  exception(0, 1) = 4;
  exception(0, 2) = 1;
  exception(1, 0) = 3;
  exception(1, 1) = 7;
  exception(1, 2) = 2;
  exception(2, 0) = 3;
  exception(2, 1) = 2;
  exception(2, 2) = 1;
  EXPECT_EQ(exception.Determinant(), 0);
  EXPECT_ANY_THROW(exception.InverseMatrix());
}

TEST(exception, calc_complementsException) {
  Matrix exception(4, 3);
  EXPECT_ANY_THROW(exception.CalcComplements());
}

TEST(exception, inverse_matrixException3) {
  Matrix exception(3, 2);
  EXPECT_ANY_THROW(exception.InverseMatrix());
}

TEST(exception, setExceprion) {
  Matrix exception(4, 4);

  EXPECT_ANY_THROW(exception.SetRows(0));
  EXPECT_ANY_THROW(exception.SetCols(-2));
}

TEST(test, plus_Exception) {
  Matrix a(2, 3);
  Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(Matrix result = a + b);
}

TEST(test, plus_Exception2) {
  Matrix a(2, 3);
  Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a += b);
}

TEST(test, plus_Exception3) {
  Matrix a(2, 3);
  Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a.SumMatrix(b));
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}