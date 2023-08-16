#ifndef imgui_glwf_window_h
#define imgui_glwf_window_h

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "model/model.h"
#include "model/model_drawer.h"

class ImguiWindow {
  public:
    glm::vec4 vertex_color;
    glm::vec4 clear_color;

    ImguiWindow();
    ~ImguiWindow();

    int LoadModel(const std::string& path);
    int MoveModel(float, float, float);
    int RotateModel(float, int);
    int ScaleModel(float, float, float);
    int DrawModel(GLuint);

    void Run() /*const*/;
    void SetingsWindow();

  private:
    GLFWwindow* window;
    std::vector<Model> models;
    ModelDrawer *drawer_;
};

#endif // imgui_glwf_window_h
