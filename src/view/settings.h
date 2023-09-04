#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <glm/glm.hpp>

#include "../imgui/imgui.h"
#include "../imgui/imfilebrowser.h"

namespace s21 {

class Settings {
public:
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

  class Builder;

public:
  std::string GetFilename();
  void Save();

private:
  Settings() {}
};

class Settings::Builder {
  private:
    Settings settings;

  public:
    Builder();

    void LoadSettings();

    Settings Build() {return settings;}
};

} // namespace s21

#endif // SETTINGS_H_ 
