#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <fstream>
#include "build/_deps/json-src/single_include/nlohmann/json.hpp"
using json = nlohmann::json;

#include <glm/glm.hpp>

#include "imgui/imfilebrowser.h"

class Settings {
public:
  Settings() : counter{0} {
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

#endif // SETTINGS_H_ 
