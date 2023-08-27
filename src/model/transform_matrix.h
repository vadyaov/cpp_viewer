#ifndef TRANSFORM_MATRIX_H_
#define TRANSFORM_MATRIX_H_

#include "../s21_matrix_oop.h"

namespace s21 {
  class TransformMatrix {
    public:
      TransformMatrix() : matr_{S21Matrix(4, 4)} {
        matr_(0, 0) = 1;
        matr_(1, 1) = 1;
        matr_(2, 2) = 1;
        matr_(3, 3) = 1;
      }

      static TransformMatrix CreateVector(float x, float y, float z) {
        TransformMatrix vector {S21Matrix(4, 1)};
        
        vector(0, 0) = x;
        vector(1, 0) = y;
        vector(2, 0) = z;
        vector(3, 0) = 1;

        return vector;
      }

      explicit TransformMatrix(const S21Matrix& matrix) : matr_{matrix} {}

      ~TransformMatrix() = default;

      /* TransformMatrix(S21Matrix&& other) : matr_{std::move(other)} { */
      /* } */

      /* TransformMatrix(const TransformMatrix& other) : matr_{other.matr_} {} */

      /* TransformMatrix& operator=(const TransformMatrix& other) { */
      /*   matr_ = other.matr_; */
      /*   return *this; */
      /* } */
      
      double& operator()(int i, int j) { return matr_(i, j); }

      TransformMatrix operator*(const TransformMatrix& other) const {
        TransformMatrix res(matr_ * other.matr_);
        return res;
      }
        
    private:
      S21Matrix matr_;
  };
} // namespace s21

#endif  // TRANSFORM_MATRIX_H_
