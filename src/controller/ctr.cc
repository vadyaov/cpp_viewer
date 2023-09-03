#include "ctr.h"

Controller* Controller::instance = 0;

void Controller::AddModel(const std::string& path) {
  models.reserve(models.size() + 1);
  Model model;
  model.LoadModel(path);
  models.push_back(std::move(model));
}

void Controller::MoveX(float dx, int counter) {
  models[counter].MoveModelX(dx);
}

void Controller::MoveY(float dy, int counter) {
  models[counter].MoveModelY(dy);
}

void Controller::MoveZ(float dz, int counter) {
  models[counter].MoveModelZ(dz);
}

void Controller::RotateX(float angle, int counter) {
  models[counter].RotateModelX(angle);
}

void Controller::RotateY(float angle, int counter) {
  models[counter].RotateModelY(angle);
}

void Controller::RotateZ(float angle, int counter) {
  models[counter].RotateModelZ(angle);
}

void Controller::Scale(float coef, int counter) {
  models[counter].Scale(coef);
}

std::size_t Controller::HowMany() const noexcept { return models.size(); }

std::size_t Controller::VertexNum(int n) const noexcept { return models[n].VertexSize(); }

std::size_t Controller::SurfaceNum(int n) const noexcept { return models[n].SurfaceSize(); }

bool Controller::Empty() const noexcept { return models.empty(); }

const _3DVertex* Controller::GetVertices(int counter) const { 
  return models[counter].GetVertexArray();
}

std::size_t Controller::GetVertexSize(int counter) const {
  return models[counter].VertexSize();
}

const _3DVertex* Controller::GetLines(int counter) const {
  return models[counter].GetLineArray();
}

std::size_t Controller::GetLinesSize(int counter) const {
  return models[counter].LinesSize();
}

const _3DVertex* Controller::GetTriangles(int counter) const {
  return models[counter].GetTriangleArray();
}

std::size_t Controller::GetTrianglesSize(int counter) const {
  return models[counter].TrianglesSize();
}
