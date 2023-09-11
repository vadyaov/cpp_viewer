#include "Aphine.h"

namespace s21 {
void Aphine::RotateModel(const CommandParameters& parameters,
                         std::vector<Vertex3D>& verticies,
                         std::vector<Vertex3D>& lines,
                         std::vector<Vertex3D>& triangles) {
  double value = parameters.value;
  if (parameters.axis == x) {
    ApplyTransformation(
        [value](auto& v) {
          float y = v.y_, z = v.z_;
          v.y_ = y * std::cos(value) - z * std::sin(value);
          v.z_ = y * std::sin(value) + z * std::cos(value);
        },
        verticies, lines, triangles);
  } else if (parameters.axis == y) {
    ApplyTransformation(
        [value](auto& v) {
          float x = v.x_, z = v.z_;
          v.x_ = x * std::cos(value) + z * std::sin(value);
          v.z_ = -x * std::sin(value) + z * std::cos(value);
        },
        verticies, lines, triangles);
  } else {
    ApplyTransformation(
        [value](auto& v) {
          float x = v.x_, y = v.y_;
          v.x_ = x * std::cos(value) - y * std::sin(value);
          v.y_ = x * std::sin(value) + y * std::cos(value);
        },
        verticies, lines, triangles);
  };
}
void Aphine::ScaleModel(const CommandParameters& parameters,
                        std::vector<Vertex3D>& verticies,
                        std::vector<Vertex3D>& lines,
                        std::vector<Vertex3D>& triangles) {
  double value = parameters.value;
  ApplyTransformation(
      [value](auto& v) {
        v.x_ *= value;
        v.y_ *= value;
        v.z_ *= value;
      },
      verticies, lines, triangles);
}

void Aphine::MoveModel(const CommandParameters& parameters,
                       std::vector<Vertex3D>& verticies,
                       std::vector<Vertex3D>& lines,
                       std::vector<Vertex3D>& triangles) {
  double value = parameters.value;
  if (parameters.axis == x) {
    ApplyTransformation([value](auto& v) { v.x_ += value; }, verticies, lines,
                        triangles);
  } else if (parameters.axis == y) {
    ApplyTransformation([value](auto& v) { v.y_ += value; }, verticies, lines,
                        triangles);
  } else {
    ApplyTransformation([value](auto& v) { v.z_ += value; }, verticies, lines,
                        triangles);
  };
}
}  // namespace s21