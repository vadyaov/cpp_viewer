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

    ~ModelDrawer();

    void SetColor(const std::string& name, const glm::vec4& color);

    void SetSize(const std::string& name, float size);

    void Draw(const std::vector<_3DVertex>& vertices, GLuint type);

    void MakeMVP(bool ortho);

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

#endif // MODEL_DRAWER_H_

