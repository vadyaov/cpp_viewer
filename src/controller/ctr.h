#ifndef CTR_H_
#define CTR_H_

#include <vector>

#include "../model/model.h"

class Controller {
  public:
    Controller() = default;
    ~Controller()  = default;

    void AddModel(const std::string& path) {
      Model model;
      model.LoadModel(path);
      models.push_back(std::move(model));
    }

    void Transform(const s21::TransformMatrix& m, int counter) {
      models[counter].TransformModel(m);
    }

    std::size_t HowMany() { return models.size(); }
    std::size_t VertexNum(int n) { return models[n].VertexSize(); }
    std::size_t SurfaceNum(int n) { return models[n].SurfaceSize(); }

    bool Empty() { return models.empty(); }

    std::vector<_3DVertex> GetVertices(int counter) { return models[counter].GetVertexArray(); }
    std::vector<_3DVertex> GetLines(int counter) { return models[counter].GetLineArray(); }
    std::vector<_3DVertex> GetTriangles(int counter) { return models[counter].GetTriangleArray(); }
    
  private:
    std::vector<Model> models;
};

#endif // CTR_H_
