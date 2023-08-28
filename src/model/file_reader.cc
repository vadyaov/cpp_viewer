#include <sstream>

#include "file_reader.h"

namespace {

  bool IsVertexLine(const std::string& line) {
    return (line.size() > 1 && line[0] == 'v' && line[1] == ' ');
  }

  bool IsSurfaceLine(const std::string& line) {
    return (line.size() > 1 && line[0] == 'f' && line[1] == ' ');
  }

  _3DVertex ReadVertex(const std::string& line) {
    std::istringstream iss(line);
    float x, y, z;
    if (!(iss >> x >> y >> z))
      throw std::invalid_argument("Incorrect vertex buffer in obj file");

    return _3DVertex{x, y, z};
  }

  std::vector<int> ReadSurface(const std::string& line) {
    std::vector<int> idx;

    std::size_t i = 2;
    while (i < line.size()) {
      std::string index;

      if (line[i] == ' ') ++i;

      while (std::isdigit(static_cast<unsigned char>(line[i])))
        index += line[i++];

      idx.push_back(std::stoi(index));

      if (line[i] == '/')
        while (i < line.size() && line[i] != ' ') ++i;
    }

    return idx;
  }
} // namespace

FileReader::FileReader(const std::string& path) : file_{path} {
      if (!file_) throw std::invalid_argument("Incorrect filename");
}

std::vector<_3DVertex> FileReader::GetVertexBuffer() {
  std::vector<_3DVertex> vertex_buf;

  std::string line;
  while (std::getline(file_, line)) {
    if (IsVertexLine(line)) {
      vertex_buf.push_back(ReadVertex(std::string(line.begin() + 2, line.end())));
    } else if (IsSurfaceLine(line)) {
      break;
    }
    pos_ = file_.tellg(); // i don't like this action every iteration
  }
  return vertex_buf;
}

std::vector<std::vector<int>> FileReader::GetSurfaceBuffer() {
  std::vector<std::vector<int>> surface_buf;
  file_.seekg(pos_);

  std::string line;
  while (std::getline(file_, line))
    if (IsSurfaceLine(line)) surface_buf.push_back(ReadSurface(line));

  return surface_buf;
}

