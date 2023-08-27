#ifndef MATRIXPLUS_INC_S21_MATRIX_OOP_H_
#define MATRIXPLUS_INC_S21_MATRIX_OOP_H_

#include <algorithm>
#include <cmath>
#include <memory>
#include <stdexcept>

constexpr double eps = 1e-7;

class S21Matrix {
 public:
  S21Matrix();
  explicit S21Matrix(const int, const int);

  S21Matrix(const S21Matrix&);
  S21Matrix& operator=(const S21Matrix&);

  S21Matrix(S21Matrix&&) noexcept;
  S21Matrix& operator=(S21Matrix&&) noexcept;

  ~S21Matrix();

  int get_rows() const noexcept;
  int get_cols() const noexcept;
  void set_rows(const int);
  void set_cols(const int);

  int size() const noexcept;
  double& operator()(const int, const int) const;

  bool EqMatrix(const S21Matrix&) const noexcept;
  void SumMatrix(const S21Matrix&);
  void SubMatrix(const S21Matrix&);
  void MulNumber(const double) noexcept;
  void MulMatrix(const S21Matrix&);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

  /* friend std::ostream& operator<<(std::ostream& os, const S21Matrix& m); */

 private:
  int rows_, cols_;
  double* matrix_;
};

S21Matrix operator-(const S21Matrix&);
bool operator==(const S21Matrix&, const S21Matrix&) noexcept;

S21Matrix& operator+=(S21Matrix&, const S21Matrix&);
S21Matrix& operator-=(S21Matrix&, const S21Matrix&);
S21Matrix& operator*=(S21Matrix&, const S21Matrix&);
S21Matrix& operator*=(S21Matrix&, const double) noexcept;

S21Matrix operator+(const S21Matrix&, const S21Matrix&);
S21Matrix operator-(const S21Matrix&, const S21Matrix&);
S21Matrix operator*(const S21Matrix&, const S21Matrix&);
S21Matrix operator*(const S21Matrix&, const double);

#endif  // MATRIXPLUS_INC_S21_MATRIX_OOP_H_
