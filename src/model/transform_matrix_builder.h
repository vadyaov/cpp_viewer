#ifndef TRANSFORM_MATRIX_BUILDER_H_
#define TRANSFORM_MATRIX_BUILDER_H_

#include "transform_matrix.h"

namespace s21 {
  class TransformMatrixBuilder {
    public:
      enum Axis {X, Y, Z};

      static TransformMatrix CreateRotationMatrix(float angle, int axis) {
        TransformMatrix matrix;

        float cos = std::cos(angle);
        float sin = std::sin(angle);

        if (axis == Axis::X) {
          matrix(1, 1) = cos;
          matrix(1, 2) = -sin;
          matrix(2, 1) = sin;
          matrix(2, 2) = cos;
        } else if (axis == Axis::Y) {
          matrix(0, 0) = cos;
          matrix(0, 2) = sin;
          matrix(2, 0) = -sin;
          matrix(2, 2) = cos;
        } else if (axis == Axis::Z) {
          matrix(0, 0) = cos;
          matrix(0, 1) = -sin;
          matrix(1, 0) = sin;
          matrix(1, 1) = cos;
        } else {
          std::cout << "Unknown axis " << axis << std::endl;
        }

        return matrix;
      }

      static TransformMatrix CreateMoveMatrix(float a, float b, float c) {
        TransformMatrix matrix;

        matrix(0, 3) = a;
        matrix(1, 3) = b;
        matrix(2, 3) = c;

        return matrix;
      }

      static TransformMatrix CreateScaleMatrix(float a, float b, float c) {
        TransformMatrix matrix;

        matrix(0, 0) = a;
        matrix(1, 1) = b;
        matrix(2, 2) = c;

        return matrix;
      }
  };
} // namespace s21

#endif  // TRANSFORM_MATRIX_BUILDER_H_
