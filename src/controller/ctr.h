#ifndef CTR_H_
#define CTR_H_

#include <vector>

#include "../model/model.h"

class Controller {
  public:
    ~Controller()  = default;

    void AddModel(const std::string& path);

    void Transform(const s21::TransformMatrix& m, int counter);

    std::size_t HowMany();
    std::size_t VertexNum(int n);
    std::size_t SurfaceNum(int n);

    bool Empty();

    std::vector<_3DVertex> GetVertices(int counter);

    std::vector<_3DVertex> GetLines(int counter);

    std::vector<_3DVertex> GetTriangles(int counter);

    static Controller* GetInstance() {
      if (!instance)
        instance = new Controller();
      return instance;
    }
    
  private:
    static Controller* instance;
    Controller() = default;
    std::vector<Model> models;
};

#endif // CTR_H_
