#include <iostream>

#include "vertex.h"
#include "transform_matrix_builder.h"

using namespace s21;

int main() {
  TransformMatrix m = TransformMatrixBuilder::CreateRotationMatrix(30, 0);
  std::cout << m;
  return 0;
}
