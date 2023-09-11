/**
 * @file Aphine.h
 * @author neelyarl heidedra
 * @brief Header file for the Aphine class.
 * @version 0.1
 * @date 2023-09-08
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef CPP4_3D_VIEWER_V_2_0_1_MODEL_APHINE_H
#define CPP4_3D_VIEWER_V_2_0_1_MODEL_APHINE_H

#include <cmath>
#include <vector>

#include "../controller/Command.h"
#include "Vertex3D.h"

namespace s21 {
/**
  @brief class for object transformations*/
class Aphine {
 public:
  Aphine(){};
  ~Aphine(){};
  /**
                 @brief moves object within given axes for given value*/
  void MoveModel(const CommandParameters& parameters,
                 std::vector<Vertex3D>& verticies, std::vector<Vertex3D>& lines,
                 std::vector<Vertex3D>& triangles);
  /**
                   @brief rotates object within given axes for given value*/
  void RotateModel(const CommandParameters& parameters,
                   std::vector<Vertex3D>& verticies,
                   std::vector<Vertex3D>& lines,
                   std::vector<Vertex3D>& triangles);
  /**
  @brief scales object for given value*/
  void ScaleModel(const CommandParameters& parameters,
                  std::vector<Vertex3D>& verticies,
                  std::vector<Vertex3D>& lines,
                  std::vector<Vertex3D>& triangles);

 private:
  template <typename Function>
  /**
    @brief applies transformation*/

  void ApplyTransformation(Function transform, std::vector<Vertex3D>& verticies,
                           std::vector<Vertex3D>& lines,
                           std::vector<Vertex3D>& triangles) {
    ApplyTransformationToVector(verticies, transform);
    ApplyTransformationToVector(lines, transform);
    ApplyTransformationToVector(triangles, transform);
  }
  template <typename VectorType, typename Function>
  /**
    @brief applies transformation for current Vertex3D(vericies,lines or
    *triangles)*/
  void ApplyTransformationToVector(VectorType& vector, Function transform) {
    for (Vertex3D& v : vector) {
      transform(v);
    }
  }
};
}  // namespace s21

#endif  // CPP4_3D_VIEWER_V_2_0_1_MODEL_APHINE_H
