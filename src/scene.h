#ifndef SCENE_H_
#define SCENE_H_

#include "figure.h"

namespace s21 {
  class Scene {
    public:


      explicit Scene(const std::vector<Figure>& figures) {
        figures_.reserve(figures.size());
        std::copy(figures.begin(), figures.end(), figures_.begin());
      }

      std::vector<Figure> GetFigure();
      void TransformFigures(TransformMatrix);

    private:
      std::vector<Figure> figures_;
  };
} // namespace s21

#endif  // SCENE_H_

