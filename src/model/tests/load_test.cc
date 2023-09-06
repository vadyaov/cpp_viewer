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

// another tests analog
