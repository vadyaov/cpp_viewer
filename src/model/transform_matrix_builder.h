#ifndef TRANSFORM_MATRIX_BUILDER_H_
#define TRANSFORM_MATRIX_BUILDER_H_

#include "transform_matrix.h"

namespace s21 {
  class TransformMatrixBuilderInterface {
    public:
      virtual TransformMatrix Build() = 0;
  };

  class RotationMatrixBuilder : public TransformMatrixBuilderInterface {
    public:
      enum Axis {X, Y, Z};
      RotationMatrixBuilder(float angle, int axis) : angle_{angle}, axis_{axis} {
      }

      TransformMatrix Build() override {
        TransformMatrix matrix;

        float cos = std::cos(angle_);
        float sin = std::sin(angle_);

        if (axis_ == Axis::X) {
          matrix(1, 1) = cos;
          matrix(1, 2) = -sin;
          matrix(2, 1) = sin;
          matrix(2, 2) = cos;
        } else if (axis_ == Axis::Y) {
          matrix(0, 0) = cos;
          matrix(0, 2) = sin;
          matrix(2, 0) = -sin;
          matrix(2, 2) = cos;
        } else if (axis_ == Axis::Z) {
          matrix(0, 0) = cos;
          matrix(0, 1) = -sin;
          matrix(1, 0) = sin;
          matrix(1, 1) = cos;
        } else {
          throw std::invalid_argument("Unknown Axis.");
        }

        return matrix;
      }

    private:
      float angle_;
      int axis_;
  };

  class MoveMatrixBuilder : public TransformMatrixBuilderInterface {
    public:
      MoveMatrixBuilder(float x, float y, float z) : dx_{x}, dy_{y}, dz_{z} {}

      TransformMatrix Build() override {
        TransformMatrix matrix;

        matrix(0, 3) = dx_;
        matrix(1, 3) = dy_;
        matrix(2, 3) = dz_;

        return matrix;
      }

    private:
      float dx_;
      float dy_;
      float dz_;
  };

  class ScaleMatrixBuilder : public TransformMatrixBuilderInterface {
    public:
      ScaleMatrixBuilder(float x, float y, float z) : dx_{x}, dy_{y}, dz_{z} {}

      TransformMatrix Build() override {
        TransformMatrix matrix;

        matrix(0, 0) = dx_;
        matrix(1, 1) = dy_;
        matrix(2, 2) = dz_;


        return matrix;
      }

    private:
      float dx_;
      float dy_;
      float dz_;
  };

} // namespace s21

#endif  // TRANSFORM_MATRIX_BUILDER_H_
