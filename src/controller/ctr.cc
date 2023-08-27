#include "ctr.h"

Controller* Controller::instance = 0;

void Controller::AddModel(const std::string& path) {
  Model model;
  model.LoadModel(path);
  models.push_back(std::move(model));
}

void Controller::Transform(const s21::TransformMatrix& m, int counter) {
  models[counter].TransformModel(m);
}

std::size_t Controller::HowMany() { return models.size(); }

std::size_t Controller::VertexNum(int n) { return models[n].VertexSize(); }

std::size_t Controller::SurfaceNum(int n) { return models[n].SurfaceSize(); }

bool Controller::Empty() { return models.empty(); }

std::vector<_3DVertex> Controller::GetVertices(int counter) { 
  return models[counter].GetVertexArray();
}

std::vector<_3DVertex> Controller::GetLines(int counter) {
  return models[counter].GetLineArray();
}

std::vector<_3DVertex> Controller::GetTriangles(int counter) {
  return models[counter].GetTriangleArray();
}
