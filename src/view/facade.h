#ifndef FACADE_H_
#define FACADE_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

#include "../model/model.h"
#include "../model/model_drawer.h"

#include "../controller/ctr.h"

class Settings;

class Facade {
  public:

    ~Facade();

    void Run() const;
    void LoadModel(const std::string&) const;
    void DrawModel(const Settings&) const;

    void SetingsWindow(Settings&) const;

    void MakeScreenShot(bool, bool) const;
    void MakeGif(int) const;

    static Facade& GetInstance() {
      static Facade instance;
      return instance;
    }

  private:
    Facade(); // Singleton class
    GLFWwindow* window;
    Controller* ctr_;
    ModelDrawer *drawer_;
};

#endif // FACADE_H_
