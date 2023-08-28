#include "model.h"

Model::Model(Model&& other) noexcept {
  surfaces_.swap(other.surfaces_);
  vertices_.swap(other.vertices_);
  lines_.swap(other.lines_);
  triangles_.swap(other.triangles_);
}

std::vector<_3DVertex> Model::GetVertexArray() const noexcept {
  return vertices_;
}

std::vector<_3DVertex> Model::GetLineArray() const noexcept {
  return lines_;
}

std::vector<_3DVertex> Model::GetTriangleArray() const noexcept {
  return triangles_;
}

std::size_t Model::VertexSize() const noexcept {return vertices_.size();}

std::size_t Model::SurfaceSize() const noexcept {return surfaces_.size();}
