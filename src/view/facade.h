#ifndef FACADE_H_
#define FACADE_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>

#include "../model/model.h"
#include "../model/model_drawer.h"

#include "../controller/ctr.h"


namespace s21 {

class Settings;

class Facade {
  public:

    ~Facade();

    void Run() const;
    void LoadModel(const std::string&) const;
    void DrawModel(const Settings&) const;

    void SetingsWindow(Settings&) const;

    void MakeScreenShot(bool, bool) const;

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

} // namespace s21

#endif // FACADE_H_
