#ifndef MODEL_H_
#define MODEL_H_

#include <vector>
#include <string>

#include "file_reader.h"
#include "transform_matrix.h"

/*
  Модель - данные, по которым будет отрисовываться графика в OpenGL:
    1. Массив вершин (x, y, z) в удобной форме.
    2. Массив поверхностей тоже желательно в удобной форме.

  Вопрос в том, какая форма удобная.
    Если нужно отрисовывать точки - то достаточно просто массива вершин.
    Если нужно отрисовывать линии - массив вершин для линий.
    Если тужно рисовать треугол-и - массив вершин для треугольников.

  Как вариант - иметь просто масив вершин и поверхностей внутри модели,
    и далее в контроллере или еще где нибудь обрабатывать их так, как требуется.
  В любом случае основа - v & f arrays.
*/

class Model {
  public:
    Model() : reader_{new FileReader()} {}
    ~Model() {
      delete reader_;
    }

    Model(Model&& other) noexcept {
      vertices_.swap(other.vertices_);
      surfaces_.swap(other.surfaces_);
      reader_ = other.reader_;
      other.reader_ = nullptr;
    }

    std::vector<_3DVertex>& GetVertexArray() {
      return vertices_;
    }

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

      print();
    }

    void TransformModel(const s21::TransformMatrix& t) {
      std::cout << "Transform:\n" << t << std::endl;
      for (_3DVertex& vertex : vertices_) {
        s21::TransformMatrix vec(vertex.x_, vertex.y_, vertex.z_);
        vec = t * vec;
        vertex.x_ = vec(0, 0);
        vertex.y_ = vec(1, 0);
        vertex.z_ = vec(2, 0);
      }
    }

    void print() {
      std::cout << "Inside Model:\n\n";
      std::cout << "Vertex Buffer:\n";
      for (const auto& i : vertices_) {
        std::cout << '(' << i.x_ << ", " << i.y_ << ", " << i.z_ << ")\n";
      }

      std::cout << "Surface Buffer:\n";
      for (const auto& i : surfaces_) {
        for (const int j : i) 
          std::cout << j << ' ';
      std::cout << std::endl;
      }
      std::cout << std::endl;
      std::cout << std::endl;
    }

  private:
    FileReader* reader_; // this stuff will parse file correctly
    std::vector<_3DVertex> vertices_;
    std::vector<std::vector<int>> surfaces_;
};

#endif // MODEL_H_
