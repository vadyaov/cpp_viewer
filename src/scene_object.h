#ifndef SCENE_OBJECT_H_
#define SCENE_OBJECT_H_

#include "transform_matrix.h"

namespace s21 {
  class SceneObject {
    virtual void Transform(TransformMatrix&) = 0;
  };
} // namespace s21

#endif  // SCENE_OBJECT_H_

