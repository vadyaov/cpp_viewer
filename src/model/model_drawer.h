#ifndef MODEL_DRAWER_H_
#define MODEL_DRAWER_H_

#include "../shaders/glshader.h"
#include "vertex.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace s21 {

class ModelDrawer {
  public:

    ~ModelDrawer();

    void SetColor(const std::string&, const glm::vec4&);

    void SetSize(const std::string&, float);

    void Draw(std::size_t, const _3DVertex*, GLuint);

    void MakeMVP(bool);

    static ModelDrawer* GetInstance() {
      if (!instance)
        instance = new ModelDrawer();
      return instance;
    }

  private:
    ModelDrawer(); // Singleton
    static ModelDrawer* instance;
    s21::Shader* shader_;
    GLuint vertex_array_;
    GLuint vertex_buffer_;
};

} // namespace s21

#endif // MODEL_DRAWER_H_

