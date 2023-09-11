#include "Model.h"

#include <cmath>

namespace s21 {
std::size_t CountLines(const std::vector<std::vector<int>>& surfaces) {
  std::size_t num = 0;
  for (const auto& surface : surfaces) {
    if (surface.size() < 2) continue;  // point
    num += surface.size() == 2 ? 1 : surface.size();
  }
  return num * 2;
}

std::size_t CountTriangles(const std::vector<std::vector<int>>& surfaces) {
  std::size_t num = 0;
  for (const auto& surface : surfaces) {
    if (surface.size() < 3)
      continue;
    else if (surface.size() == 3)
      ++num;
    else
      num += surface.size() - 2;
  }
  return num * 3;
}

Model::Model(Model&& other) noexcept {
  surfaces_.swap(other.surfaces_);
  vertices_.swap(other.vertices_);
  lines_.swap(other.lines_);
  triangles_.swap(other.triangles_);
}

const Vertex3D& Model::GetVertexArray() const noexcept {
  return vertices_.front();
}

const Vertex3D& Model::GetLineArray() const noexcept { return lines_.front(); }

const Vertex3D& Model::GetTriangleArray() const noexcept {
  return triangles_.front();
}

std::size_t Model::VertexSize() const noexcept { return vertices_.size(); }

std::size_t Model::LinesSize() const noexcept { return lines_.size(); }

std::size_t Model::TrianglesSize() const noexcept { return triangles_.size(); }

std::size_t Model::SurfaceSize() const noexcept { return surfaces_.size(); }

void Model::LoadModel(const std::string& path) {
  FileReader reader(path);

  vertices_ = reader.GetVertexBuffer();
  surfaces_ = reader.GetSurfaceBuffer();

  lines_.resize(CountLines(surfaces_));
  MakeLines();

  triangles_.resize(CountTriangles(surfaces_));
  MakeTriangles();
}

void Model::ApplyAphine(const Command& command) {
  const CommandParameters pars = command.GetParameters();
  if (pars.type == Move) {
    aphine.MoveModel(pars, vertices_, lines_, triangles_);
  } else if (pars.type == Rotation) {
    aphine.RotateModel(pars, vertices_, lines_, triangles_);
  } else {
    aphine.ScaleModel(pars, vertices_, lines_, triangles_);
  }
}

void Model::MakeLines() {
  std::size_t c = 0;
  for (const auto& surface : surfaces_) {
    for (std::size_t j = 0; j < surface.size() - 1; ++j) {
      lines_[c++] = (vertices_[surface[j] - 1]);
      lines_[c++] = (vertices_[surface[j + 1] - 1]);
    }
    if (surface.size() > 2) {
      lines_[c++] = (vertices_[surface.back() - 1]);
      lines_[c++] = (vertices_[surface.front() - 1]);
    }
  }
}

void s21::Model::MakeTriangles() {
  std::size_t c = 0;
  for (const auto& surface : surfaces_) {
    if (surface.size() < 3) continue;

    std::size_t j = 1;
    for (; j < surface.size() - 1; ++j) {
      triangles_[c++] = (vertices_[surface[0] - 1]);
      triangles_[c++] = (vertices_[surface[j] - 1]);
      triangles_[c++] = (vertices_[surface[j + 1] - 1]);
    }
  }
}
}  // namespace s21
