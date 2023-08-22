#ifndef MODEL_DRAWER_H_
#define MODEL_DRAWER_H_

#include "../shaders/glshader.h"
#include "vertex.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ModelDrawer {
  public:
    ModelDrawer() : shader_{new s21::Shader("shaders/versh.glsl",
                                      "shaders/fragm.glsl")} {
      glEnable(GL_PROGRAM_POINT_SIZE);

      glGenVertexArrays(1, &vertex_array_);
      glBindVertexArray(vertex_array_);

      glGenBuffers(1, &vertex_buffer_);
      glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);

      shader_->use();

    }

    ~ModelDrawer() {
      glDeleteVertexArrays(1, &vertex_array_);
      glDeleteBuffers(1, &vertex_buffer_);
      delete shader_;
    }

    void SetColor(const std::string& name, const glm::vec4& color) {
      shader_->setVec4(name, color);
    }

    void SetSize(const std::string& name, float size) {
      shader_->setFloat(name, size);
    }

    void Draw(const std::vector<_3DVertex>& vertices, GLuint type) {

      glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_); // lishnee na vsiakiy

      glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(_3DVertex),
                   &vertices.front(), GL_STATIC_DRAW);
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, nullptr);
      glBindVertexArray(vertex_array_);

      glDrawArrays(type, 0, vertices.size());
    }

    void MakeMVP(bool ortho) {
      glm::mat4 model = glm::mat4(1.0f);
      glm::mat4 view = glm::mat4(1.0f);
      glm::mat4 projection = glm::mat4(1.0f);

      /* model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, -3.0f)); */
      view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
      if (ortho)
        projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -50.1f, 50.0f);
      else
        projection = glm::perspective(glm::radians(45.0f), 1280.0f / 750.0f, 0.1f, 100.0f);

      unsigned int model_loc = glGetUniformLocation(shader_->ID, "model");
      unsigned int view_loc = glGetUniformLocation(shader_->ID, "view");

      glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model));
      glUniformMatrix4fv(view_loc, 1, GL_FALSE, &view[0][0]);
      shader_->setMat4("projection", projection);
    }

  private:
    s21::Shader* shader_;
    GLuint vertex_array_;
    GLuint vertex_buffer_;
};

#endif // MODEL_DRAWER_H_

