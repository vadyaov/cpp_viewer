#ifndef POINT_H_
#define POINT_H_

/* What about noexcept ? */

/* По идее ни один из публичных методов не будет выбрасывать исключений,
 * нужно ли писать noexcept ? */

namespace s21 {
  class Point {
    public:
      Point() : x_{0}, y_{0}, z_{0} {}
      Point(float x, float y, float z) : x_{x}, y_{y}, z_{z} {}
      Point(const Point& other) : x_{other.x_}, y_{other.y_}, z_{other.z_} {}
      Point& operator=(const Point& other) {
        x_ = other.x_;
        y_ = other.y_;
        z_ = other.z_;

        return *this;
      }

      /* нужны ли перемещающие конструктор и равно для такого простого класса? */
      /* Point(Point&&) noexcept; */
      /* Point& operator=(Point&&); */

    private:
      float x_;
      float y_;
      float z_;
  };
} // namespace s21

#endif  // POINT_H_
