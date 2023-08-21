#ifndef imgui_glwf_window_h
#define imgui_glwf_window_h

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imfilebrowser.h"

#include "model/model.h"
#include "model/model_drawer.h"

class ImguiWindow {
  public:
    class Settings {
      public:
        Settings() : clear_color{0.1f, 0.1f, 0.25f, 1.0f},
                     vertex_color{0.1f, 0.1f, 0.25f, 1.0f},
                     lines_color{0.2f, 1.5f, 0.25f, 1.0f},
                     triangles_color{0.215f, 0.5f, 0.11f, 1.0f} {
          counter = 0;
          file_dialog.SetTitle("Browse");
          file_dialog.SetTypeFilters({".obj"});
        }
                     
        ~Settings() {
        }

        std::string GetFilename() {
          std::string name = "";
          if (!filenames.empty())
            name = filenames[counter];
          return name;
        }

      int counter;
      glm::vec4 clear_color;
      glm::vec4 vertex_color;
      glm::vec4 lines_color;
      glm::vec4 triangles_color;
      ImGui::FileBrowser file_dialog;
      std::vector<std::string> filenames;
    };

    ImguiWindow();
    ~ImguiWindow();

    int LoadModel(const std::string& path, Settings& s);
    int MoveModel(float, float, float, int);
    int RotateModel(float, int, int);
    int ScaleModel(float, int);
    int DrawModel(const Settings&);

    void Run() /*const*/;
    void SetingsWindow(Settings&);

    std::size_t Size() const noexcept { return models.size(); }

  private:
    GLFWwindow* window;
    std::vector<Model> models;
    ModelDrawer *drawer_;
};

#endif // imgui_glwf_window_h
