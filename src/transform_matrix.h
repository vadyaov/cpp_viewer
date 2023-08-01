#ifndef TRANSFORM_MATRIX_H_
#define TRANSFORM_MATRIX_H_

#include "lmatrix/inc/s21_matrix_oop.h"
#include "point.h"

namespace s21 {
  class TransformMatrix {
    public:
      TransformMatrix() : matr_{S21Matrix(4, 4)} {
        matr_(0, 0) = 1;
        matr_(1, 1) = 1;
        matr_(2, 2) = 1;
        matr_(3, 3) = 1;
      }
      ~TransformMatrix() = default;

      TransformMatrix(const TransformMatrix& other) : matr_{other.matr_} {}
      /* TransformMatrix(TransformMatrix&& other) noexcept : matr_{std::move(other.matr_)} {} */

      TransformMatrix& operator=(const TransformMatrix& other) {
        TransformMatrix m(other);
        std::swap(m, *this);
        return *this;
      }
      
      /* TransformMatrix& operator=(TransformMatrix&& other) noexcept { */
      /*   std::swap(matr_, other.matr_); */
      /*   return *this; */
      /* } */

      double& operator()(int i, int j) { return matr_(i, j); }

      TransformMatrix operator*(const TransformMatrix& other) const;
        
      /* Point TransformPoint(const Point& point) const; */

      friend std::ostream& operator<<(std::ostream& os, const TransformMatrix& matrix) {
        os << matrix.matr_;
        return os;
      }

    private:
      S21Matrix matr_;
  };
} // namespace s21

#endif  // TRANSFORM_MATRIX_H_
