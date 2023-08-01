#ifndef FACADE_H_
#define FACADE_H_

#include "transform_matrix_builder.h"
#include "scene.h" /*"scene_drawer.h" change later*/
#include "file_reader.h"

namespace s21 {
  class Facade {
    public:
      Facade();

      // later change 'int' by 'FacadeOperationResult'
      int DrawScene();
      int LoadScene(const std::string& path);
      int MoveScene();
      int RotateScene();
      int ScaleScene();
    private:
      /* FileReader reader_; */ // NOT EVEN A TYPE
      /* SceneDrawer drawer_; */
      Scene scene_;
  };
} // namespace s21

#endif  // FACADE_H_
