#include <gtest/gtest.h>

#include "../model.h"

#include <iostream>

bool operator==(const _3DVertex& lhs, const _3DVertex& rhs) {
  return lhs.x_ == rhs.x_ && lhs.y_ == rhs.y_ && lhs.z_ == rhs.z_;
}

TEST(load_test, t1) {
  s21::Model model;
  const std::string path {"../models/cube.obj"};

  std::vector<_3DVertex> expected_vertices {{1.0f, -1.0f, -1.0f},
                                            {1.0f, -1.0f, 1.0f},
                                            {-1.0f, -1.0f, 1.0f},
                                            {-1.0f, -1.0f, -1.0f},
                                            {1.0f, 1.0f, -0.999999f},
                                            {0.999999, 1.0f, 1.000001f},
                                            {-1.0f, 1.0f, 1.0f},
                                            {-1.0f, 1.0f, -1.0f}};

  std::vector<_3DVertex> expected_lines {{1.0f, -1.0f, -1.0f}, {1.0f, -1.0f, 1.0f},
                                         {1.0f, -1.0f, 1.0f}, {-1.0f, -1.0f, 1.0f},
                                         {-1.0f, -1.0f, 1.0f}, {-1.0f, -1.0f, -1.0f},
                                         {-1.0f, -1.0f, -1.0f}, {1.0f, -1.0f, -1.0f},
                                          {1.0f, -1.0f, -1.0f}, {1.0f, -1.0f, 1.0f},
                                          {1.0f, -1.0f, 1.0f}, {0.999999, 1.0f, 1.000001f},
                                          {0.999999, 1.0f, 1.000001f}, {1.0f, 1.0f, -0.999999f},
                                          {1.0f, 1.0f, -0.999999f}, {1.0f, -1.0f, -1.0f},
                                          {1.0f, 1.0f, -0.999999f}, {0.999999, 1.0f, 1.000001f},
                                          {0.999999, 1.0f, 1.000001f}, {-1.0f, 1.0f, 1.0f},
                                          {-1.0f, 1.0f, 1.0f}, {-1.0f, 1.0f, -1.0f},
                                          {-1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, -0.999999f},
                                          {-1.0f, -1.0f, 1.0f}, {-1.0f, -1.0f, -1.0f},
                                          {-1.0f, -1.0f, -1.0f}, {-1.0f, 1.0f, -1.0f},
                                          {-1.0f, 1.0f, -1.0f}, {-1.0f, 1.0f, 1.0f},
                                          {-1.0f, 1.0f, 1.0f}, {-1.0f, -1.0f, 1.0f},
                                          {1.0f, -1.0f, 1.0f}, {-1.0f, -1.0f, 1.0f},
                                          {-1.0f, -1.0f, 1.0f}, {-1.0f, 1.0f, 1.0f},
                                          {-1.0f, 1.0f, 1.0f}, {0.999999, 1.0f, 1.000001f},
                                          {0.999999, 1.0f, 1.000001f}, {1.0f, -1.0f, 1.0f},
                                          {1.0f, -1.0f, -1.0f}, {1.0f, 1.0f, -0.999999f},
                                          {1.0f, 1.0f, -0.999999f}, {-1.0f, 1.0f, -1.0f},
                                          {-1.0f, 1.0f, -1.0f}, {-1.0f, -1.0f, -1.0f},
                                          {-1.0f, -1.0f, -1.0f}, {1.0f, -1.0f, -1.0f}};

  std::vector<_3DVertex> expected_triangles {expected_vertices[0], expected_vertices[1], expected_vertices[2],
                                             expected_vertices[0], expected_vertices[2], expected_vertices[3],
                                             expected_vertices[0], expected_vertices[1], expected_vertices[5],
                                             expected_vertices[0], expected_vertices[5], expected_vertices[4],
                                             expected_vertices[4], expected_vertices[5], expected_vertices[6],
                                             expected_vertices[4], expected_vertices[6], expected_vertices[7],
                                             expected_vertices[2], expected_vertices[3], expected_vertices[7],
                                             expected_vertices[2], expected_vertices[7], expected_vertices[6],
                                             expected_vertices[1], expected_vertices[2], expected_vertices[6],
                                             expected_vertices[1], expected_vertices[6], expected_vertices[5],
                                             expected_vertices[0], expected_vertices[4], expected_vertices[7],
                                             expected_vertices[0], expected_vertices[7], expected_vertices[3],
  };

  model.LoadModel(path);

  EXPECT_EQ(model.VertexSize(), 8);

  const _3DVertex* expect_v = &expected_vertices.front();
  const _3DVertex* getted_v = model.GetVertexArray();

  for (std::size_t i = 0; i < model.VertexSize(); ++i)
    EXPECT_EQ(expect_v[i], getted_v[i]);

  EXPECT_EQ(model.LinesSize(), 48);

  const _3DVertex* expect_l = &expected_lines.front();
  const _3DVertex* getted_l = model.GetLineArray();

  for (std::size_t i = 0; i < model.LinesSize(); ++i)
    EXPECT_EQ(expect_l[i], getted_l[i]);

  EXPECT_EQ(model.TrianglesSize(), 36);

  const _3DVertex* expect_t = &expected_triangles.front();
  const _3DVertex* getted_t = model.GetTriangleArray();

  for (std::size_t i = 0; i < model.TrianglesSize(); ++i)
    EXPECT_EQ(expect_t[i], getted_t[i]);
}

TEST(load_test, t2) {
  s21::Model model;
  const std::string path {"../models/prism.obj"};

  std::vector<_3DVertex> expected_vertices {{4.5973f, -4.8484f, -0.0f},
                                            {0.0f, -4.8484f, 7.9628f},
                                            {-4.5973f, -4.8484f, -0.0f},
                                            {-0.0f, 4.8484f, 7.9628f},
                                            {-4.5973f, 4.8484f, -0.0f},
                                            {4.5973f, 4.8484f, -0.0f}};

  std::vector<_3DVertex> expected_lines {{4.5973, -4.8484, -0.0000}, {0.0000, -4.8484, 7.9628},
    {0.0000,  -4.8484, 7.9628},  {-4.5973, -4.8484, -0.0000}, {-4.5973, -4.8484, -0.0000},
    {4.5973, -4.8484, -0.0000}, {-4.5973, -4.8484, -0.0000}, {0.0000,  -4.8484, 7.9628},
    {0.0000,  -4.8484, 7.9628},  {-0.0000, 4.8484,  7.9628},  {-0.0000, 4.8484, 7.9628},
    {-4.5973, 4.8484,  -0.0000}, {-4.5973, 4.8484,  -0.0000}, {-4.5973, -4.8484, -0.0000},
    {0.0000,  -4.8484, 7.9628},  {4.5973,  -4.8484, -0.0000}, {4.5973,  -4.8484, -0.0000},
    {4.5973,  4.8484,  -0.0000}, {4.5973,  4.8484, -0.0000}, {-0.0000, 4.8484, 7.9628},
    {-0.0000, 4.8484,  7.9628},  {0.0000, -4.8484, 7.9628},  {4.5973,  -4.8484, -0.0000},
    {-4.5973, -4.8484, -0.0000}, {-4.5973, -4.8484, -0.0000}, {-4.5973, 4.8484,  -0.0000},
    {-4.5973, 4.8484, -0.0000}, {4.5973,  4.8484,  -0.0000}, {4.5973,  4.8484,  -0.0000},
    {4.5973, -4.8484, -0.0000}, {4.5973,  4.8484,  -0.0000}, {-4.5973, 4.8484,  -0.0000},
    {-4.5973, 4.8484,  -0.0000}, {-0.0000, 4.8484,  7.9628},  {-0.0000, 4.8484, 7.9628},
    {4.5973,  4.8484,  -0.0000}};

  std::vector<_3DVertex> expected_triangles {
      {4.5973,  -4.8484, -0.0000}, {0.0000,  -4.8484, 7.9628}, {-4.5973, -4.8484, -0.0000},
      {-4.5973, -4.8484, -0.0000}, {0.0000,  -4.8484, 7.9628}, {-0.0000, 4.8484, 7.9628},
      {-4.5973, -4.8484, -0.0000}, {-0.0000, 4.8484, 7.9628}, {-4.5973f, 4.8484f, -0.0f},
      {0.0000,  -4.8484, 7.9628}, {4.5973,  -4.8484, -0.0000}, {4.5973,  4.8484,  -0.0000},
      {0.0000,  -4.8484, 7.9628}, {4.5973,  4.8484,  -0.0000}, {-0.0f, 4.8484f, 7.9628f},
      {4.5973,  -4.8484, -0.0000}, {-4.5973, -4.8484, -0.0000}, {-4.5973, 4.8484,  -0.0000},
      {4.5973,  -4.8484, -0.0000}, {-4.5973, 4.8484,  -0.0000}, {4.5973f, 4.8484f, -0.0f},
      {4.5973, 4.8484,  -0.0000}, {-4.5973, 4.8484,  -0.0000}, {-0.0000, 4.8484,  7.9628}
  };

  model.LoadModel(path);

  EXPECT_EQ(model.VertexSize(), 6);

  const _3DVertex* expect_v = &expected_vertices.front();
  const _3DVertex* getted_v = model.GetVertexArray();

  for (std::size_t i = 0; i < model.VertexSize(); ++i)
    EXPECT_EQ(expect_v[i], getted_v[i]);

  EXPECT_EQ(model.LinesSize(), 36);

  const _3DVertex* expect_l = &expected_lines.front();
  const _3DVertex* getted_l = model.GetLineArray();

  for (std::size_t i = 0; i < model.LinesSize(); ++i)
    EXPECT_EQ(expect_l[i], getted_l[i]);

  EXPECT_EQ(model.TrianglesSize(), 24);

  const _3DVertex* expect_t = &expected_triangles.front();
  const _3DVertex* getted_t = model.GetTriangleArray();

  for (std::size_t i = 0; i < model.TrianglesSize(); ++i)
    EXPECT_EQ(expect_t[i], getted_t[i]);
}

TEST(load_test, t3) {
  s21::Model model;
  const std::string path {"../models/pyramid.obj"};

  std::vector<_3DVertex> expected_vertices {{0, 0, 0},
                                            {1, 0, 0},
                                            {1, 1, 0},
                                            {0, 1, 0},
                                            {0.5, 0.5, 1.6}};

  std::vector<_3DVertex> expected_lines {{0, 1, 0}, {0, 0, 0}, {0, 0, 0}, {1, 0, 0}, {1, 0, 0},
    {0, 1, 0}, {1, 1, 0}, {0, 1, 0}, {0, 1, 0}, {1, 0, 0}, {1, 0, 0}, {1, 1, 0},
    {0.5, 0.5, 1.6}, {1, 0, 0}, {1, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0.5, 0.5, 1.6},
    {0, 1, 0}, {0.5, 0.5, 1.6}, {0.5, 0.5, 1.6}, {0, 0, 0}, {0, 0, 0}, {0, 1, 0},
    {1, 1, 0}, {0.5, 0.5, 1.6}, {0.5, 0.5, 1.6}, {0, 1, 0}, {0, 1, 0}, {1, 1, 0},
    {0.5, 0.5, 1.6}, {1, 1, 0}, {1, 1, 0}, {1, 0, 0}, {1, 0, 0}, {0.5, 0.5, 1.6}};

  std::vector<_3DVertex> expected_triangles {
    {0, 1, 0}, {0, 0, 0}, {1, 0, 0}, // 4 1 2
    {1, 1, 0}, {0, 1, 0}, {1, 0, 0}, // 3 4 2
    {0.5, 0.5, 1.6}, {1, 0, 0}, {0, 0, 0}, // 5 2 1
    {0, 1, 0}, {0.5, 0.5, 1.6}, {0, 0, 0}, // 4 5 1
    {1, 1, 0}, {0.5, 0.5, 1.6}, {0, 1, 0}, // 3 5 4
    {0.5, 0.5, 1.6}, {1, 1, 0}, {1, 0, 0} // 5 3 2
  };

  model.LoadModel(path);

  EXPECT_EQ(model.VertexSize(), 5);

  const _3DVertex* expect_v = &expected_vertices.front();
  const _3DVertex* getted_v = model.GetVertexArray();

  for (std::size_t i = 0; i < model.VertexSize(); ++i)
    EXPECT_EQ(expect_v[i], getted_v[i]);

  EXPECT_EQ(model.LinesSize(), 36);

  const _3DVertex* expect_l = &expected_lines.front();
  const _3DVertex* getted_l = model.GetLineArray();

  for (std::size_t i = 0; i < model.LinesSize(); ++i)
    EXPECT_EQ(expect_l[i], getted_l[i]);

  EXPECT_EQ(model.TrianglesSize(), 18);

  const _3DVertex* expect_t = &expected_triangles.front();
  const _3DVertex* getted_t = model.GetTriangleArray();

  for (std::size_t i = 0; i < model.TrianglesSize(); ++i)
    EXPECT_EQ(expect_t[i], getted_t[i]);
}

TEST(load_test, t4) {
  s21::Model model;
  const std::string path {"../models/prism.obj"};

  std::vector<_3DVertex> expected_vertices {
    {4.5973, -4.8484, -0.0000},
    {0.0000, -4.8484, 7.9628},
    {-4.5973, -4.8484, -0.0000},
    {-0.0000, 4.8484, 7.9628},
    {-4.5973, 4.8484, -0.0000},
    {4.5973, 4.8484, -0.0000}};

  std::vector<_3DVertex> expected_lines {
      {4.5973,  -4.8484, -0.0000}, {0.0000,  -4.8484, 7.9628},
      {0.0000,  -4.8484, 7.9628}, {-4.5973, -4.8484, -0.0000},
      {-4.5973, -4.8484, -0.0000}, {4.5973, -4.8484, -0.0000},
      {-4.5973, -4.8484, -0.0000}, {0.0000,  -4.8484, 7.9628},
      {0.0000,  -4.8484, 7.9628}, {-0.0000, 4.8484,  7.9628},
      {-0.0000, 4.8484, 7.9628}, {-4.5973, 4.8484,  -0.0000},
      {-4.5973, 4.8484,  -0.0000}, {-4.5973, -4.8484, -0.0000},
      {0.0000,  -4.8484, 7.9628}, {4.5973,  -4.8484, -0.0000},
      {4.5973,  -4.8484, -0.0000}, {4.5973,  4.8484,  -0.0000},
      {4.5973,  4.8484, -0.0000}, {-0.0000, 4.8484,  7.9628},
      {-0.0000, 4.8484,  7.9628}, {0.0000, -4.8484, 7.9628},
      {4.5973,  -4.8484, -0.0000}, {-4.5973, -4.8484, -0.0000},
      {-4.5973, -4.8484, -0.0000}, {-4.5973, 4.8484,  -0.0000},
      {-4.5973, 4.8484, -0.0000}, {4.5973,  4.8484,  -0.0000},
      {4.5973,  4.8484,  -0.0000}, {4.5973, -4.8484, -0.0000},
      {4.5973,  4.8484,  -0.0000}, {-4.5973, 4.8484,  -0.0000},
      {-4.5973, 4.8484,  -0.0000}, {-0.0000, 4.8484,  7.9628},
      {-0.0000, 4.8484, 7.9628}, {4.5973,  4.8484,  -0.0000}
  };

  std::vector<_3DVertex> expected_triangles {
    {4.5973, -4.8484, -0.0000}, {0.0000, -4.8484, 7.9628}, {-4.5973, -4.8484, -0.0000}, // 1 2 3
    {-4.5973, -4.8484, -0.0000}, {0.0000, -4.8484, 7.9628}, {-0.0000, 4.8484, 7.9628}, // 3 2 4
    {-4.5973, -4.8484, -0.0000}, {-0.0000, 4.8484, 7.9628}, {-4.5973, 4.8484, -0.0000}, // 3 4 5
    {0.0000, -4.8484, 7.9628}, {4.5973, -4.8484, -0.0000}, {4.5973, 4.8484, -0.0000}, // 2 1 6
    {0.0000, -4.8484, 7.9628}, {4.5973, 4.8484, -0.0000}, {-0.0000, 4.8484, 7.9628}, // 2 6 4
    {4.5973, -4.8484, -0.0000}, {-4.5973, -4.8484, -0.0000}, {-4.5973, 4.8484, -0.0000}, // 1 3 5
    {4.5973, -4.8484, -0.0000}, {-4.5973, 4.8484, -0.0000}, {4.5973, 4.8484, -0.0000}, // 1 5 6
    {4.5973, 4.8484, -0.0000}, {-4.5973, 4.8484, -0.0000}, {-0.0000, 4.8484, 7.9628} // 6 5 4
  };

  model.LoadModel(path);

  EXPECT_EQ(model.VertexSize(), 6);

  const _3DVertex* expect_v = &expected_vertices.front();
  const _3DVertex* getted_v = model.GetVertexArray();

  for (std::size_t i = 0; i < model.VertexSize(); ++i)
    EXPECT_EQ(expect_v[i], getted_v[i]);

  EXPECT_EQ(model.LinesSize(), 36);

  const _3DVertex* expect_l = &expected_lines.front();
  const _3DVertex* getted_l = model.GetLineArray();

  for (std::size_t i = 0; i < model.LinesSize(); ++i)
    EXPECT_EQ(expect_l[i], getted_l[i]);

  EXPECT_EQ(model.TrianglesSize(), 24);

  const _3DVertex* expect_t = &expected_triangles.front();
  const _3DVertex* getted_t = model.GetTriangleArray();

  for (std::size_t i = 0; i < model.TrianglesSize(); ++i)
    /* std::cout << getted_t[i].x_ << ' ' << getted_t[i].y_ << ' ' << getted_t[i].z_ << std::endl; */
    EXPECT_EQ(expect_t[i], getted_t[i]);
}
