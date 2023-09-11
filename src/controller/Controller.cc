
#include "Controller.h"
namespace s21 {
Controller* Controller::instance = 0;

void Controller::AddModel(const std::string& path) {
  models.reserve(models.size() + 1);
  Model model;
  model.LoadModel(path);
  models.push_back(std::move(model));
}

std::size_t Controller::HowMany() const noexcept { return models.size(); }

std::size_t Controller::VertexNum(int n) const noexcept {
  return models[n].VertexSize();
}

std::size_t Controller::SurfaceNum(int n) const noexcept {
  return models[n].SurfaceSize();
}

bool Controller::Empty() const noexcept { return models.empty(); }

const Vertex3D& Controller::GetVertices(int counter) const {
  return models[counter].GetVertexArray();
}

std::size_t Controller::GetVertexSize(int counter) const {
  return models[counter].VertexSize();
}

const Vertex3D& Controller::GetLines(int counter) const {
  return models[counter].GetLineArray();
}

std::size_t Controller::GetLinesSize(int counter) const {
  return models[counter].LinesSize();
}

const Vertex3D& Controller::GetTriangles(int counter) const {
  return models[counter].GetTriangleArray();
}

std::size_t Controller::GetTrianglesSize(int counter) const {
  return models[counter].TrianglesSize();
}

}  // namespace s21
