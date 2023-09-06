#ifndef MODEL_H_
#define MODEL_H_

#include <vector>

#include "file_reader.h"

namespace s21 {

class Model {
  public:
    Model() {}
    ~Model() {}

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
    void MoveModelZ(float);

    void RotateModelX(float);
    void RotateModelY(float);
    void RotateModelZ(float);

    void Scale(float);

    template <typename Function>
      void ApplyTransformation(Function transform) {
        ApplyTransformationToVector(vertices_, transform);
        ApplyTransformationToVector(lines_, transform);
        ApplyTransformationToVector(triangles_, transform);
      }

    template <typename VectorType, typename Function>
      void ApplyTransformationToVector(VectorType& vector, Function transform) {
        for (_3DVertex& v : vector) {
            transform(v);
        }
      }

  private:
    std::vector<_3DVertex> vertices_;
    std::vector<_3DVertex> lines_;
    std::vector<_3DVertex> triangles_;

    std::vector<std::vector<int>> surfaces_;
};

} // namespace s21

#endif // MODEL_H_
