#ifndef VERTEX_H_
#define VERTEX_H_

#include "point.h"
#include "scene_object.h"

namespace s21 {
  class Vertex : public SceneObject {
    public:
      Vertex() : position_() {}
      Vertex(float x, float y, float z) : position_(x, y, z) {}
      explicit Vertex(const Point& p) : position_{p} {}
      Vertex(const Vertex& other) : position_{other.position_} {}
      Vertex& operator=(const Vertex& other) {
        position_ = other.position_;
        return *this;
      }

      /* нужны ли перемещающие операции ? */

      /* Vertex(Vertex&& other) noexcept; */
      /* Vertex& operator=(Vertex&& other) noexcept; */

      Point get_position() { return position_; } // getter

      void Transform(TransformMatrix& m) override {
      }

      friend std::ostream& operator<<(std::ostream& os, const Vertex& v) {
        return os << v.position_;
      }

    private:
      Point position_;
  };
} // namespace s21

#endif  // VERTEX_H_

