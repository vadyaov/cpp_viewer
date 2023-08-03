#ifndef FIGURE_H_
#define FIGURE_H_

#include <vector>

#include "edge.h"

namespace s21 {
  class Figure : public SceneObject {
    public:
      Figure() = default;
      Figure(const std::vector<Vertex>& vertices,
             const std::vector<Edge>& edges) : vertices_(vertices), edges_(edges) {}

      /* std::vector<Vertex> GetVertices(); */
      /* std::vector<Edge> GetEdges(); */

      void Transform(TransformMatrix &m) override {
      }

      void print() const {
        std::cout << "Vertices:\n";
        for (const auto& v : vertices_)
          std::cout << v << std::endl;

        std::cout << "Edges:\n";
        for (const auto& e : edges_)
          std::cout << e << std::endl;
      }


    private:
      std::vector<Vertex> vertices_;
      std::vector<Edge> edges_;
  };
} // namespace s21


#endif  // FIGURE_H_

