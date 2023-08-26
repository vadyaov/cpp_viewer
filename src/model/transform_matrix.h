#ifndef TRANSFORM_MATRIX_H_
#define TRANSFORM_MATRIX_H_

#include "../matrix_lib/inc/s21_matrix_oop.h"

namespace s21 {
  class TransformMatrix {
    public:
      TransformMatrix() : matr_{S21Matrix(4, 4)} {
        matr_(0, 0) = 1;
        matr_(1, 1) = 1;
        matr_(2, 2) = 1;
        matr_(3, 3) = 1;
      }

      TransformMatrix(float x, float y, float z) : matr_{S21Matrix(4, 1)} {
        matr_(0, 0) = x;
        matr_(1, 0) = y;
        matr_(2, 0) = z;
        matr_(3, 0) = 1;
      }

      ~TransformMatrix() = default;

      explicit TransformMatrix(S21Matrix&& other) : matr_{std::move(other)} {
      }

      TransformMatrix(const TransformMatrix& other) : matr_{other.matr_} {}

      TransformMatrix& operator=(const TransformMatrix& other) {
        matr_ = other.matr_;
        return *this;
      }
      
      double& operator()(int i, int j) { return matr_(i, j); }

      TransformMatrix operator*(const TransformMatrix& other) const {
        TransformMatrix res(matr_ * other.matr_);
        return res;
      }
        
      /* friend std::ostream& operator<<(std::ostream& os, const TransformMatrix& matrix) { */
      /*   os << matrix.matr_; */
      /*   return os; */
      /* } */

    private:
      S21Matrix matr_;
  };
} // namespace s21

#endif  // TRANSFORM_MATRIX_H_
