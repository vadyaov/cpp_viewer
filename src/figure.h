#ifndef FIGURE_H_
#define FIGURE_H_

#include <vector>

#include "vertex.h"

namespace s21 {
  class Figure : public SceneObject {
    public:
      Figure() = default;
      explicit Figure(const std::vector<Vertex>& vertices) {
        vertices_.reserve(vertices.size());
        std::copy(vertices.begin(), vertices.end(), vertices_.begin());
      }

      std::vector<Vertex> GetVertices();
      /* std::vector<Edge> GetEdges(); */
      void Transform(TransformMatrix &m) override {
      }

    private:
      std::vector<Vertex> vertices_;
      /* std::vector<Edge> edges_; */
  };
} // namespace s21

#endif  // FIGURE_H_

