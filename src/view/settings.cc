#include "settings.h"

#include <fstream>
#include "../build/_deps/json-src/single_include/nlohmann/json.hpp"
using json = nlohmann::json;

#include "../imgui/imgui.h"
#include "../imgui/imfilebrowser.h"

std::string Settings::GetFilename() {
    std::string name = "";
    if (!filenames.empty())
      name = filenames[counter];
    return name;
  }

void Settings::Builder::LoadSettings() {
    std::ifstream file("savefile.json");
    if (file.is_open()) {
      json json;
      file >> json;

    settings.clear_color.x = json["clear_color"].at(0);
    settings.clear_color.y = json["clear_color"].at(1);
    settings.clear_color.z = json["clear_color"].at(2);
    settings.clear_color.w = 1;

    settings.vertex_color.x = json["vertex_color"].at(0);
    settings.vertex_color.y = json["vertex_color"].at(1);
    settings.vertex_color.z = json["vertex_color"].at(2);
    settings.vertex_color.w = 1;

    settings.lines_color.x = json["lines_color"].at(0);
    settings.lines_color.y = json["lines_color"].at(1);
    settings.lines_color.z = json["lines_color"].at(2);
    settings.lines_color.w = 1;

    settings.triangles_color.x = json["triangles_color"].at(0);
    settings.triangles_color.y = json["triangles_color"].at(1);
    settings.triangles_color.z = json["triangles_color"].at(2);
    settings.triangles_color.w = 1;

    settings.filenames.push_back(json["last_filename"]);

    settings.points = json["points"];
    settings.lines = json["lines"];
    settings.triangles = json["tringles"];

    settings.move_speed = json["move_speed"];
    settings.point_size = json["point_size"];
    settings.line_width = json["line_width"];

    settings.rounded = json["rounded"];
    settings.ortho = json["ortho"];
    settings.bmp = json["bmp"];
    settings.jpg = json["jpg"];

    }
  }

void Settings::Save() {
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

    std::ofstream file("savefile.json");
    if (file.is_open()) {
      file << json.dump(4);
    }
  }

Settings::Builder::Builder() {
  settings.counter = 0;
  settings.file_dialog.SetTitle("Browse");
  settings.file_dialog.SetTypeFilters({".obj"});
  LoadSettings();
}
