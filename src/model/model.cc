#include "model.h"

#include <cmath>
#include <iostream>

namespace {
 std::size_t CountLines(const std::vector<std::vector<int>>& surfaces) {
   std::size_t num = 0;
   for (const auto& surface : surfaces) {
     if (surface.size() < 2) continue; // point
     num += surface.size() == 2 ? 1 : surface.size();
   }
   return num * 2;
  }

   std::size_t CountTriangles(const std::vector<std::vector<int>>& surfaces) {
     std::size_t num = 0;
     for (const auto& surface : surfaces) {
       if (surface.size() < 3) continue;
       else if (surface.size() == 3) ++num;
       else
         num += surface.size() - 2;
     }
     return num * 3;
   }

} // namespace

s21::Model::Model(Model&& other) noexcept {
  surfaces_.swap(other.surfaces_);
  vertices_.swap(other.vertices_);
  lines_.swap(other.lines_);
  triangles_.swap(other.triangles_);
}

const _3DVertex* s21::Model::GetVertexArray() const noexcept {
  return &vertices_.front();
}

const _3DVertex* s21::Model::GetLineArray() const noexcept {
  return &lines_.front();
}

const _3DVertex* s21::Model::GetTriangleArray() const noexcept {
  return &triangles_.front();
}

std::size_t s21::Model::VertexSize() const noexcept {return vertices_.size();}

std::size_t s21::Model::LinesSize() const noexcept {return lines_.size();}

std::size_t s21::Model::TrianglesSize() const noexcept {return triangles_.size();}

std::size_t s21::Model::SurfaceSize() const noexcept {return surfaces_.size();}

void s21::Model::LoadModel(const std::string& path) {
  std::cout << path << std::endl;
  FileReader reader(path);

  vertices_ = reader.GetVertexBuffer();
  surfaces_ = reader.GetSurfaceBuffer();
  
  lines_.resize(CountLines(surfaces_));
  MakeLines();

  triangles_.resize(CountTriangles(surfaces_));
  MakeTriangles();

}

void s21::Model::MakeLines() {
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

void s21::Model::MoveModelX(float range) {
  ApplyTransformation([range](auto& v) {
      v.x_ += range;
  });
}

void s21::Model::MoveModelY(float range) {
  ApplyTransformation([range](auto& v) {
      v.y_ += range;
  });
}

void s21::Model::MoveModelZ(float range) {
  ApplyTransformation([range](auto& v) {
      v.z_ += range;
  });
}

void s21::Model::RotateModelX(float angle) {
  ApplyTransformation([angle](auto& v) {
    float y = v.y_, z = v.z_;
    v.y_ = y * std::cos(angle) - z * std::sin(angle);
    v.z_ = y * std::sin(angle) + z * std::cos(angle);
  });
}

void s21::Model::RotateModelY(float angle) {
  ApplyTransformation([angle](auto& v) {
    float x = v.x_, z = v.z_;
    v.x_ = x * std::cos(angle) + z * std::sin(angle);
    v.z_ = -x * std::sin(angle) + z * std::cos(angle);
  });
}

void s21::Model::RotateModelZ(float angle) {
  ApplyTransformation([angle](auto& v) {
    float x = v.x_, y = v.y_;
    v.x_ = x * std::cos(angle) - y * std::sin(angle);
    v.y_ = x * std::sin(angle) + y * std::cos(angle);
  });
}

void s21::Model::Scale(float n) {
  ApplyTransformation([n](auto& v) {
    v.x_ *= n;
    v.y_ *= n;
    v.z_ *= n;
  });
}
