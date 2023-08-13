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
    ImguiWindow();
    ~ImguiWindow();

    int LoadModel(const std::string& path);
    int MoveModel(float ax, float ay, float az);
    int DrawModel();

    void Run() /*const*/;
    void SetingsWindow();

  private:
    GLFWwindow* window;
    std::vector<Model> models;
    ModelDrawer *drawer_;

};

#endif // imgui_glwf_window_h
