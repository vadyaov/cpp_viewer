#include "ctr.h"

Controller* Controller::instance = 0;

void Controller::AddModel(const std::string& path) {
  Model model;
  model.LoadModel(path);
  models.push_back(std::move(model));
}

void Controller::Transform(const s21::TransformMatrix& m, int counter) {
  if (models.empty()) return;
  models[counter].TransformModel(m);
}

void Controller::Move(float x, float y, float z, int counter) {
  Transform(s21::MoveMatrixBuilder(x, y, z).Build(), counter);
}

void Controller::Rotate(float angle, int axis, int counter) {
  Transform(s21::RotationMatrixBuilder(angle, axis).Build(), counter);
}

void Controller::Scale(float coef, int counter) {
  Transform(s21::ScaleMatrixBuilder(coef, coef, coef).Build(), counter);
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
