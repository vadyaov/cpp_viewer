#include "ctr.h"

s21::Controller* s21::Controller::instance = 0;

void s21::Controller::AddModel(const std::string& path) {
  models.reserve(models.size() + 1);
  Model model;
  model.LoadModel(path);
  models.push_back(std::move(model));
}

void s21::Controller::MoveX(float dx, int counter) {
  models[counter].MoveModelX(dx);
}

void s21::Controller::MoveY(float dy, int counter) {
  models[counter].MoveModelY(dy);
}

void s21::Controller::MoveZ(float dz, int counter) {
  models[counter].MoveModelZ(dz);
}

void s21::Controller::RotateX(float angle, int counter) {
  models[counter].RotateModelX(angle);
}

void s21::Controller::RotateY(float angle, int counter) {
  models[counter].RotateModelY(angle);
}

void s21::Controller::RotateZ(float angle, int counter) {
  models[counter].RotateModelZ(angle);
}

void s21::Controller::Scale(float coef, int counter) {
  models[counter].Scale(coef);
}

std::size_t s21::Controller::HowMany() const noexcept { return models.size(); }

std::size_t s21::Controller::VertexNum(int n) const noexcept { return models[n].VertexSize(); }

std::size_t s21::Controller::SurfaceNum(int n) const noexcept { return models[n].SurfaceSize(); }

bool s21::Controller::Empty() const noexcept { return models.empty(); }

const _3DVertex* s21::Controller::GetVertices(int counter) const { 
  return models[counter].GetVertexArray();
}

std::size_t s21::Controller::GetVertexSize(int counter) const {
  return models[counter].VertexSize();
}

const _3DVertex* s21::Controller::GetLines(int counter) const {
  return models[counter].GetLineArray();
}

std::size_t s21::Controller::GetLinesSize(int counter) const {
  return models[counter].LinesSize();
}

const _3DVertex* s21::Controller::GetTriangles(int counter) const {
  return models[counter].GetTriangleArray();
}

std::size_t s21::Controller::GetTrianglesSize(int counter) const {
  return models[counter].TrianglesSize();
}
