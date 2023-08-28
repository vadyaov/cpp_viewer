#ifndef imgui_glwf_window_h
#define imgui_glwf_window_h

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imfilebrowser.h"

#include "model/model.h"
#include "model/model_drawer.h"

#include "controller/ctr.h"

class Settings;

class ImguiWindow {
  public:

    ~ImguiWindow();

    void Run() const;
    int LoadModel(const std::string&) const;
    int DrawModel(const Settings&) const;

    void SetingsWindow(Settings&) const;

    void MakeScreenShot(bool, bool) const;
    void MakeGif(int) const;

    static ImguiWindow& GetInstance() {
      static ImguiWindow instance;
      return instance;
    }

  private:
    ImguiWindow(); // Singleton class
    GLFWwindow* window;
    Controller* ctr_;
    ModelDrawer *drawer_;
};

#endif // imgui_glwf_window_h
