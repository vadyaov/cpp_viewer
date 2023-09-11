/**
 * @file model_drawer.h
 * @author neelyarl heidedra
 * @brief Header file for the ModelDraer class.
 * @version 0.1
 * @date 2023-09-08
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef CPP4_3D_VIEWER_V_2_0_1_MODEL_DRAWER_H
#define CPP4_3D_VIEWER_V_2_0_1_MODEL_DRAWER_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../shaders/glshader.h"
#include "Model.h"

namespace s21 {
/**
  @brief class for model visualisation*/
class ModelDrawer {
 public:
  ~ModelDrawer();
  /**
      @brief sets color to shader*/
  void SetColor(const std::string&, const glm::vec4&);
  /**
      @brief sets size to shader*/
  void SetSize(const std::string&, float);
  /**
      @brief draws verticies, lines or triangles*/

  void Draw(std::size_t, const Vertex3D*, GLuint);
  /**
   @brief sets view projection of model*/
  void MakeMVP(bool);
  /**
      @brief returns instance of a class*/
  static ModelDrawer* GetInstance() {
    if (!instance) instance = new ModelDrawer();
    return instance;
  }

 private:
  ModelDrawer();  // Singleton
  static ModelDrawer* instance;
  s21::Shader* shader_;
  GLuint vertex_array_;
  GLuint vertex_buffer_;
};

}  // namespace s21

#endif  // CPP4_3D_VIEWER_V_2_0_1_MODEL_DRAWER_H
