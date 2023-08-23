#ifndef imgui_glwf_window_h
#define imgui_glwf_window_h

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include "build/_deps/json-src/single_include/nlohmann/json.hpp"
using json = nlohmann::json;

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
        Settings() : counter{0},
                     clear_color{0.1f, 0.1f, 0.25f, 1.0f},
                     vertex_color{1.0f, 1.0f, 1.0f, 1.0f},
                     lines_color{0.2f, 1.5f, 0.25f, 1.0f},
                     triangles_color{0.215f, 0.5f, 0.11f, 1.0f},
                     points {false}, lines{true}, triangles{true},
                     move_speed{0.2f}, point_size{0.0}, line_width{1.0f},
                     rounded{false}, ortho{false}, bmp{false}, jpg{false} {

          file_dialog.SetTitle("Browse");
          file_dialog.SetTypeFilters({".obj"});

          LoadSettings("savefile.json");
        }
                     
        ~Settings() {
          SaveSettings("savefile.json");
        }

        std::string GetFilename() {
          std::string name = "";
          if (!filenames.empty())
            name = filenames[counter];
          return name;
        }

        void LoadSettings(const std::string& path) {
          std::ifstream file(path);
          if (file.is_open()) {
            json json;
            file >> json;

          clear_color.x = json["clear_color"].at(0);
          clear_color.y = json["clear_color"].at(1);
          clear_color.z = json["clear_color"].at(2);
          clear_color.w = 1;

          vertex_color.x = json["vertex_color"].at(0);
          vertex_color.y = json["vertex_color"].at(1);
          vertex_color.z = json["vertex_color"].at(2);
          vertex_color.w = 1;

          lines_color.x = json["lines_color"].at(0);
          lines_color.y = json["lines_color"].at(1);
          lines_color.z = json["lines_color"].at(2);
          lines_color.w = 1;

          triangles_color.x = json["triangles_color"].at(0);
          triangles_color.y = json["triangles_color"].at(1);
          triangles_color.z = json["triangles_color"].at(2);
          triangles_color.w = 1;

          filenames.push_back(json["last_filename"]);

          points = json["points"];
          lines = json["lines"];
          triangles = json["tringles"];

          move_speed = json["move_speed"];
          point_size = json["point_size"];
          line_width = json["line_width"];

          rounded = json["rounded"];
          ortho = json["ortho"];
          bmp = json["bmp"];
          jpg = json["jpg"];

          }
        }

        void SaveSettings(const std::string& path) {
          json json;
          json["clear_color"].push_back(clear_color.x);
          json["clear_color"].push_back(clear_color.y);
          json["clear_color"].push_back(clear_color.z);

          json["vertex_color"].push_back(vertex_color.x);
          json["vertex_color"].push_back(vertex_color.y);
          json["vertex_color"].push_back(vertex_color.z);

          json["lines_color"].push_back(lines_color.x);
          json["lines_color"].push_back(lines_color.y);
          json["lines_color"].push_back(lines_color.z);

          json["triangles_color"].push_back(triangles_color.x);
          json["triangles_color"].push_back(triangles_color.y);
          json["triangles_color"].push_back(triangles_color.z);

          json["last_filename"] = filenames.back();

          json["points"] = points;
          json["lines"] = lines;
          json["tringles"] = triangles;

          json["move_speed"] = move_speed;
          json["point_size"] = point_size;
          json["line_width"] = line_width;

          json["rounded"] = rounded;
          json["ortho"] = ortho;
          json["bmp"] = bmp;
          json["jpg"] = jpg;

          std::ofstream file(path);
          if (file.is_open()) {
            file << json.dump(4);
          }
        }

      int counter;
      glm::vec4 clear_color;
      glm::vec4 vertex_color;
      glm::vec4 lines_color;
      glm::vec4 triangles_color;
      ImGui::FileBrowser file_dialog;
      std::vector<std::string> filenames;
      bool points, lines, triangles;
      float move_speed;
      float point_size;
      float line_width;
      bool rounded;
      bool ortho;
      bool bmp, jpg;
    };

    ImguiWindow();
    ~ImguiWindow();

    int LoadModel(const std::string& path, Settings& s);
    int MoveModel(float, float, float, int);
    int RotateModel(float, int, int);
    int ScaleModel(float, int);
    int DrawModel(const Settings&);
    void MakeScreenShot(bool, bool);

    void Run() /*const*/;
    void SetingsWindow(Settings&);

    std::size_t Size() const noexcept { return models.size(); }

  private:
    GLFWwindow* window;
    std::vector<Model> models;
    ModelDrawer *drawer_;
};

#endif // imgui_glwf_window_h
