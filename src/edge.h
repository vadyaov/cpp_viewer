#ifndef EDGE_H_
#define EDGE_H_

/* What about noexcept ? */

/* По идее ни один из публичных методов не будет выбрасывать исключений,
 * нужно ли писать noexcept ? */

#include "vertex.h"

namespace s21 {
  class Edge {
    public:
      Edge() = delete;
      Edge(Vertex& b, Vertex& e) : begin_(b), end_(e) {}

      Vertex& GetBegin() const noexcept {return begin_;}
      Vertex& GetEnd() const noexcept {return end_;}

      friend std::ostream& operator<<(std::ostream& os, const s21::Edge& p);

    private:
      Vertex& begin_;
      Vertex& end_;
  };

std::ostream& operator<<(std::ostream& os, const s21::Edge& p) {
  os << "{" << p.begin_ << ", " << p.end_ << "}";
  return os;
}

} // namespace s21



#endif  // EDGE_H_
