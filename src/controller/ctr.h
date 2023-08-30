#ifndef CTR_H_
#define CTR_H_

#include <vector>

#include "../model/model.h"

class Controller {
  public:
    ~Controller()  = default;

    void AddModel(const std::string& path);

    void MoveX(float, int);
    void MoveY(float, int);

    // mb add this idk
    /* void MoveZ(float, int); */

    void RotateX(float, int);
    void RotateY(float, int);
    void RotateZ(float, int);

    void Scale(float, int);

    std::size_t HowMany() const noexcept;
    std::size_t VertexNum(int n) const noexcept;
    std::size_t SurfaceNum(int n) const noexcept;

    bool Empty() const noexcept;

    const _3DVertex* GetVertices(int) const;
    std::size_t GetVertexSize(int counter) const;

    const _3DVertex* GetLines(int) const;
    std::size_t GetLinesSize(int counter) const;

    const _3DVertex* GetTriangles(int) const;
    std::size_t GetTrianglesSize(int counter) const;

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
