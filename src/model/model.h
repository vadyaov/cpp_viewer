#ifndef MODEL_H_
#define MODEL_H_

#include <vector>

#include "file_reader.h"
#include "transform_matrix.h"

class Model {
  public:
    Model() = default;
    ~Model() = default;

    Model(Model&& other) noexcept;

    std::vector<_3DVertex> GetVertexArray() const noexcept;

    std::vector<_3DVertex> GetLineArray() const noexcept;

    std::vector<_3DVertex> GetTriangleArray() const noexcept;

    std::size_t VertexSize() const noexcept;
    std::size_t SurfaceSize() const noexcept;

    void LoadModel(const std::string& path) {
      FileReader reader(path);

      vertices_ = reader.GetVertexBuffer();
      surfaces_ = reader.GetSurfaceBuffer();
      
      lines_.reserve(CountLines(surfaces_));
      MakeLines();

      triangles_.reserve(CountTriangles(surfaces_));
      MakeTriangles();

    }

    void MakeLines() {
      lines_.clear();
      for (const auto& surface : surfaces_) {
        for (std::size_t j = 0; j < surface.size() - 1; ++j) {
          lines_.push_back(vertices_[surface[j] - 1]);
          lines_.push_back(vertices_[surface[j + 1] - 1]);
        }
        if (surface.size() > 2) {
          lines_.push_back(vertices_[surface.back() - 1]);
          lines_.push_back(vertices_[surface.front() - 1]);
        }
      }
    }

    void MakeTriangles() {
      triangles_.clear();
      for (const auto& surface : surfaces_) {
        if (surface.size() < 3) continue;

        std::size_t j = 1;
        for (; j < surface.size() - 1; ++j) {
          triangles_.push_back(vertices_[surface[0] - 1]);
          triangles_.push_back(vertices_[surface[j] - 1]);
          triangles_.push_back(vertices_[surface[j + 1] - 1]);
        }
      }
    }

     std::size_t CountLines(const std::vector<std::vector<int>>& surfaces) const {
       std::size_t num = 0;
       for (const auto& surface : surfaces) {
         if (surface.size() < 2) continue;
         num += surface.size() == 2 ? 1 : surface.size();
       }

       return num * 2;
     }

     std::size_t CountTriangles(const std::vector<std::vector<int>>& surfaces) const {
       std::size_t num = 0;
       for (const auto& surface : surfaces) {
         if (surface.size() < 3) continue;
         num += surface.size() == 3 ? 1 : surface.size() - 1;
       }

       return num * 3;
     }

    void TransformModel(const s21::TransformMatrix& t) {
      for (_3DVertex& vertex : vertices_) {
        s21::TransformMatrix res = t *
          s21::TransformMatrix::CreateVector(vertex.x_, vertex.y_, vertex.z_);
        vertex.x_ = res(0, 0);
        vertex.y_ = res(1, 0);
        vertex.z_ = res(2, 0);
      }

      MakeLines();
      MakeTriangles();

    }

    /* void print() { */
    /*   std::cout << "Inside Model:\n\n"; */
    /*   std::cout << "Vertex Buffer:\n"; */
    /*   for (const auto& i : vertices_) { */
    /*     std::cout << '(' << i.x_ << ", " << i.y_ << ", " << i.z_ << ")\n"; */
    /*   } */
    /*   std::cout << std::endl; */
    /* } */

  private:
    std::vector<_3DVertex> vertices_;
    std::vector<_3DVertex> lines_;
    std::vector<_3DVertex> triangles_;

    std::vector<std::vector<int>> surfaces_;
};

#endif // MODEL_H_
