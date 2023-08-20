#ifndef MODEL_H_
#define MODEL_H_

#include <vector>
#include <string>

#include "file_reader.h"
#include "transform_matrix.h"

class Model {
  public:
    Model() : reader_{new FileReader()} {}
    ~Model() { delete reader_; }

    Model(Model&& other) noexcept {
      surfaces_.swap(other.surfaces_);
      vertices_.swap(other.vertices_);
      lines_.swap(other.lines_);
      triangles_.swap(other.triangles_);

      reader_ = other.reader_;
      other.reader_ = nullptr;
    }

    std::vector<_3DVertex> GetVertexArray() const { return vertices_; }

    std::vector<_3DVertex> GetLineArray() const { return lines_; }

    std::vector<_3DVertex> GetTriangleArray() const { return triangles_; }

    void LoadModel(const std::string& path) {

      try {
        std::cout << "start loading model...\n";
        reader_->LoadModel(path);
        std::cout << "end loading model...\n";
      } catch (const std::exception& e) {
        std::cout << "Loading Model Error.\n"; // delete after
        throw;
      }

      vertices_ = reader_->GetVertexBuffer();
      surfaces_ = reader_->GetSurfaceBuffer();
      
      lines_.reserve(CountLines(surfaces_));
      MakeLines();

      triangles_.reserve(CountTriangles(surfaces_));
      MakeTriangles();

      std::cout << "vertex size = " << vertices_.size() << std::endl;
      std::cout << "surface size = " << surfaces_.size() << std::endl;
      std::cout << "lines size = " << lines_.size() << std::endl;
      std::cout << "triangle size = " << triangles_.size() << std::endl;

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

        for (std::size_t j = 0; j < surface.size() - 2; ++j) {
          triangles_.push_back(vertices_[surface[j] - 1]);
          triangles_.push_back(vertices_[surface[j + 1] - 1]);
          triangles_.push_back(vertices_[surface[j + 2] - 1]);
        }
        if (surface.size() > 3) {
          triangles_.push_back(vertices_[surface[surface.size() - 2] - 1]);
          triangles_.push_back(vertices_[surface[surface.size() - 1] - 1]);
          triangles_.push_back(vertices_[surface.front() - 1]);
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
        s21::TransformMatrix vec(vertex.x_, vertex.y_, vertex.z_);
        vec = t * vec;
        vertex.x_ = vec(0, 0);
        vertex.y_ = vec(1, 0);
        vertex.z_ = vec(2, 0);
      }

      MakeLines();
      MakeTriangles();

    }

    void print() {
      std::cout << "Inside Model:\n\n";
      std::cout << "Vertex Buffer:\n";
      for (const auto& i : vertices_) {
        std::cout << '(' << i.x_ << ", " << i.y_ << ", " << i.z_ << ")\n";
      }
      std::cout << std::endl;
    }

  private:
    FileReader* reader_;

    std::vector<_3DVertex> vertices_;
    std::vector<_3DVertex> lines_;
    std::vector<_3DVertex> triangles_;

    std::vector<std::vector<int>> surfaces_;
};

#endif // MODEL_H_
