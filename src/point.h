#ifndef POINT_H_
#define POINT_H_

/* What about noexcept ? */

/* По идее ни один из публичных методов не будет выбрасывать исключений,
 * нужно ли писать noexcept ? */

#include <iostream>

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

      friend std::ostream& operator<<(std::ostream& os, const s21::Point& p);

      /* float& operator[](int i) { */
      /*   if (i < 0 || i > 2) throw std::out_of_range("out of range"); */
      /* } */

    public:
      float x_;
      float y_;
      float z_;
  };

std::ostream& operator<<(std::ostream& os, const s21::Point& p) {
  os << "(" << p.x_ << ", " << p.y_ << ", " << p.z_ << ")";
  return os;
}

} // namespace s21



#endif  // POINT_H_
