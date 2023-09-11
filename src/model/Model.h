/**
 * @file model.h
 * @author neelyarl heidedra
 * @brief Header file for the Model class.
 * @version 0.1
 * @date 2023-09-08
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef CPP4_3D_VIEWER_V_2_0_1_MODEL_MODEL_H
#define CPP4_3D_VIEWER_V_2_0_1_MODEL_MODEL_H

#include <GLFW/glfw3.h>

#include <string>
#include <vector>

#include "../controller/Command.h"
#include "./Vertex3D.h"
#include "Aphine.h"
#include "Reader.h"
namespace s21 {
/**
    @brief deals with object*/
class Model {
 public:
  Model(){};
  ~Model(){};

  Model(Model&& other) noexcept;
  /**
      @brief vertex array getter*/
  const Vertex3D& GetVertexArray() const noexcept;
  /**
      @brief lines array getter*/

  const Vertex3D& GetLineArray() const noexcept;
  /**
    @brief triangles array getter*/
  const Vertex3D& GetTriangleArray() const noexcept;
  /**
      @brief vertex array size getter*/
  std::size_t VertexSize() const noexcept;
  /**
    @brief lines array size getter*/
  std::size_t LinesSize() const noexcept;
  /**
    @brief triangles array size getter*/
  std::size_t TrianglesSize() const noexcept;
  /**
  @brief surfaces array size getter*/
  std::size_t SurfaceSize() const noexcept;
  /**
      @brief loads model from file*/
  void LoadModel(const std::string&);
  /**
      @brief applies aphine transformations to model*/
  void ApplyAphine(const Command& command);

 private:
  std::vector<Vertex3D> vertices_;
  std::vector<Vertex3D> lines_;
  std::vector<Vertex3D> triangles_;

  std::vector<std::vector<int>> surfaces_;
  Aphine aphine;

 private:
  /**
    @brief creates lines farray form vericies*/
  void MakeLines();
  /**
      @brief creates traingles array from verticies*/
  void MakeTriangles();
};

}  // namespace s21

#endif  // CPP4_3D_VIEWER_V_2_0_1_MODEL_MODEL_H
