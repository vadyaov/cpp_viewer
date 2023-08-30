#ifndef MODEL_H_
#define MODEL_H_

#include <vector>

#include "file_reader.h"

class Model {
  public:
    Model() = default;
    ~Model() = default;

    Model(Model&& other) noexcept;

    const _3DVertex* GetVertexArray() const noexcept;

    const _3DVertex* GetLineArray() const noexcept;

    const _3DVertex* GetTriangleArray() const noexcept;

    std::size_t VertexSize() const noexcept;
    std::size_t LinesSize() const noexcept;
    std::size_t TrianglesSize() const noexcept;
    std::size_t SurfaceSize() const noexcept;

    void LoadModel(const std::string&);

    void MakeLines();

    void MakeTriangles();

    void MoveModelX(float);
    void MoveModelY(float);

    void RotateModelX(float);
    void RotateModelY(float);
    void RotateModelZ(float);

    void Scale(float);

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
