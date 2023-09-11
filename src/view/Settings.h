/**
 * @file settings.h
 * @author neelyarl heidedra
 * @brief Header file for the Settings class.
 * @version 0.1
 * @date 2023-09-08
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef CPP4_3D_VIEWER_V_2_0_1_VIEW_SETTINGS_H
#define CPP4_3D_VIEWER_V_2_0_1_VIEW_SETTINGS_H

#include <glm/glm.hpp>

#include "../imgui/imgui.h"
#include "./../imgui/imfilebrowser.h"

namespace s21 {
/**
  @brief stores and reproduces app's settings*/
class Settings {
 public:
  int counter;
  glm::vec4 clear_color, vertex_color, lines_color, triangles_color;
  ImGui::FileBrowser file_dialog;
  std::vector<std::string> filenames;
  bool points, lines, triangles, rounded, ortho, bmp, jpg, strippled;
  float move_speed, point_size;
  int line_width;

  class Builder;

 public:
  /**
     @brief file name getter*/
  std::string GetFilename();
  /**
  @brief saves settings*/
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

  Settings Build() { return settings; }
};

}  // namespace s21

#endif  // CPP4_3D_VIEWER_V_2_0_1_VIEW_SETTINGS_H
