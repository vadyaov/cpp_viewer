#include <gtest/gtest.h>

#include "../model/Model.h"
#include "./../model/Aphine.h"
#include "./../model/Vertex3D.h"

using namespace s21;
TEST(load_test, t1) {
  s21::Model model;
  const std::string path{"models/cube.obj"};

  std::vector<Vertex3D> expected_vertices{
      {1.0f, -1.0f, -1.0f},     {1.0f, -1.0f, 1.0f},
      {-1.0f, -1.0f, 1.0f},     {-1.0f, -1.0f, -1.0f},
      {1.0f, 1.0f, -0.999999f}, {0.999999, 1.0f, 1.000001f},
      {-1.0f, 1.0f, 1.0f},      {-1.0f, 1.0f, -1.0f}};

  std::vector<Vertex3D> expected_lines{
      {1.0f, -1.0f, -1.0f},        {1.0f, -1.0f, 1.0f},
      {1.0f, -1.0f, 1.0f},         {-1.0f, -1.0f, 1.0f},
      {-1.0f, -1.0f, 1.0f},        {-1.0f, -1.0f, -1.0f},
      {-1.0f, -1.0f, -1.0f},       {1.0f, -1.0f, -1.0f},
      {1.0f, -1.0f, -1.0f},        {1.0f, -1.0f, 1.0f},
      {1.0f, -1.0f, 1.0f},         {0.999999, 1.0f, 1.000001f},
      {0.999999, 1.0f, 1.000001f}, {1.0f, 1.0f, -0.999999f},
      {1.0f, 1.0f, -0.999999f},    {1.0f, -1.0f, -1.0f},
      {1.0f, 1.0f, -0.999999f},    {0.999999, 1.0f, 1.000001f},
      {0.999999, 1.0f, 1.000001f}, {-1.0f, 1.0f, 1.0f},
      {-1.0f, 1.0f, 1.0f},         {-1.0f, 1.0f, -1.0f},
      {-1.0f, 1.0f, -1.0f},        {1.0f, 1.0f, -0.999999f},
      {-1.0f, -1.0f, 1.0f},        {-1.0f, -1.0f, -1.0f},
      {-1.0f, -1.0f, -1.0f},       {-1.0f, 1.0f, -1.0f},
      {-1.0f, 1.0f, -1.0f},        {-1.0f, 1.0f, 1.0f},
      {-1.0f, 1.0f, 1.0f},         {-1.0f, -1.0f, 1.0f},
      {1.0f, -1.0f, 1.0f},         {-1.0f, -1.0f, 1.0f},
      {-1.0f, -1.0f, 1.0f},        {-1.0f, 1.0f, 1.0f},
      {-1.0f, 1.0f, 1.0f},         {0.999999, 1.0f, 1.000001f},
      {0.999999, 1.0f, 1.000001f}, {1.0f, -1.0f, 1.0f},
      {1.0f, -1.0f, -1.0f},        {1.0f, 1.0f, -0.999999f},
      {1.0f, 1.0f, -0.999999f},    {-1.0f, 1.0f, -1.0f},
      {-1.0f, 1.0f, -1.0f},        {-1.0f, -1.0f, -1.0f},
      {-1.0f, -1.0f, -1.0f},       {1.0f, -1.0f, -1.0f}};

  std::vector<Vertex3D> expected_triangles{
      expected_vertices[0], expected_vertices[1], expected_vertices[2],
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

  const Vertex3D* expect_v = &expected_vertices.front();
  const Vertex3D* getted_v = &model.GetVertexArray();

  for (std::size_t i = 0; i < model.VertexSize(); ++i) {
    EXPECT_EQ(expect_v[i].x_, getted_v[i].x_);
    EXPECT_EQ(expect_v[i].y_, getted_v[i].y_);
    EXPECT_EQ(expect_v[i].z_, getted_v[i].z_);
  }

  EXPECT_EQ(model.LinesSize(), 48);

  const Vertex3D* expect_l = &expected_lines.front();
  const Vertex3D* getted_l = &model.GetLineArray();

  for (std::size_t i = 0; i < model.LinesSize(); ++i) {
    EXPECT_EQ(expect_l[i].x_, getted_l[i].x_);
    EXPECT_EQ(expect_l[i].y_, getted_l[i].y_);
    EXPECT_EQ(expect_l[i].z_, getted_l[i].z_);
  }

  EXPECT_EQ(model.TrianglesSize(), 36);

  const Vertex3D* expect_t = &expected_triangles.front();
  const Vertex3D* getted_t = &model.GetTriangleArray();

  for (std::size_t i = 0; i < model.TrianglesSize(); ++i) {
    EXPECT_EQ(expect_t[i].x_, getted_t[i].x_);
    EXPECT_EQ(expect_t[i].y_, getted_t[i].y_);
    EXPECT_EQ(expect_t[i].z_, getted_t[i].z_);
  }
}

TEST(move_test_x, t1) {
  s21::Model model;
  const std::string path{"models/cube.obj"};

  std::vector<Vertex3D> expected_vertices{
      {2.0f, -1.0f, -1.0f},     {2.0f, -1.0f, 1.0f},
      {0.f, -1.0f, 1.0f},       {0.f, -1.0f, -1.0f},
      {2.0f, 1.0f, -0.999999f}, {1.999999, 1.0f, 1.000001f},
      {0.f, 1.0f, 1.0f},        {0.f, 1.0f, -1.0f}};

  std::vector<Vertex3D> expected_lines{
      {2.0f, -1.0f, -1.0f},        {2.0f, -1.0f, 1.0f},
      {2.0f, -1.0f, 1.0f},         {0.f, -1.0f, 1.0f},
      {0.f, -1.0f, 1.0f},          {0.f, -1.0f, -1.0f},
      {0.f, -1.0f, -1.0f},         {2.0f, -1.0f, -1.0f},
      {2.0f, -1.0f, -1.0f},        {2.0f, -1.0f, 1.0f},
      {2.0f, -1.0f, 1.0f},         {1.999999, 1.0f, 1.000001f},
      {1.999999, 1.0f, 1.000001f}, {2.0f, 1.0f, -0.999999f},
      {2.0f, 1.0f, -0.999999f},    {2.0f, -1.0f, -1.0f},
      {2.0f, 1.0f, -0.999999f},    {1.999999, 1.0f, 1.000001f},
      {1.999999, 1.0f, 1.000001f}, {0.f, 1.0f, 1.0f},
      {0.f, 1.0f, 1.0f},           {0.f, 1.0f, -1.0f},
      {0.f, 1.0f, -1.0f},          {2.0f, 1.0f, -0.999999f},
      {0.f, -1.0f, 1.0f},          {0.f, -1.0f, -1.0f},
      {0.f, -1.0f, -1.0f},         {0.f, 1.0f, -1.0f},
      {0.f, 1.0f, -1.0f},          {0.f, 1.0f, 1.0f},
      {0.f, 1.0f, 1.0f},           {0.f, -1.0f, 1.0f},
      {2.0f, -1.0f, 1.0f},         {0.f, -1.0f, 1.0f},
      {0.f, -1.0f, 1.0f},          {0.f, 1.0f, 1.0f},
      {0.f, 1.0f, 1.0f},           {1.999999, 1.0f, 1.000001f},
      {1.999999, 1.0f, 1.000001f}, {2.0f, -1.0f, 1.0f},
      {2.0f, -1.0f, -1.0f},        {2.0f, 1.0f, -0.999999f},
      {2.0f, 1.0f, -0.999999f},    {0.f, 1.0f, -1.0f},
      {0.f, 1.0f, -1.0f},          {0.f, -1.0f, -1.0f},
      {0.f, -1.0f, -1.0f},         {2.0f, -1.0f, -1.0f}};

  std::vector<Vertex3D> expected_triangles{
      expected_vertices[0], expected_vertices[1], expected_vertices[2],
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
  Command command;
  CommandParameters pars = {Move, x, 1.0};
  command.UpdateParameters(pars);
  model.ApplyAphine(command);
  const Vertex3D* expect_v = &expected_vertices.front();
  const Vertex3D* getted_v = &model.GetVertexArray();

  for (std::size_t i = 0; i < model.VertexSize(); ++i) {
    EXPECT_EQ(expect_v[i].x_, getted_v[i].x_);
    EXPECT_EQ(expect_v[i].y_, getted_v[i].y_);
    EXPECT_EQ(expect_v[i].z_, getted_v[i].z_);
  }

  EXPECT_EQ(model.LinesSize(), 48);

  const Vertex3D* expect_l = &expected_lines.front();
  const Vertex3D* getted_l = &model.GetLineArray();

  for (std::size_t i = 0; i < model.LinesSize(); ++i) {
    EXPECT_EQ(expect_l[i].x_, getted_l[i].x_);
    EXPECT_EQ(expect_l[i].y_, getted_l[i].y_);
    EXPECT_EQ(expect_l[i].z_, getted_l[i].z_);
  }

  EXPECT_EQ(model.TrianglesSize(), 36);

  const Vertex3D* expect_t = &expected_triangles.front();
  const Vertex3D* getted_t = &model.GetTriangleArray();

  for (std::size_t i = 0; i < model.TrianglesSize(); ++i) {
    EXPECT_EQ(expect_t[i].x_, getted_t[i].x_);
    EXPECT_EQ(expect_t[i].y_, getted_t[i].y_);
    EXPECT_EQ(expect_t[i].z_, getted_t[i].z_);
  }
}

TEST(move_test_y, t1) {
  s21::Model model;
  const std::string path{"models/cube.obj"};

  std::vector<Vertex3D> expected_vertices{
      {1.0f, -2.0f, -1.0f},    {1.0f, -2.0f, 1.0f},
      {-1.0f, -2.0f, 1.0f},    {-1.0f, -2.0f, -1.0f},
      {1.0f, 0.f, -0.999999f}, {0.999999, 0.f, 1.000001f},
      {-1.0f, 0.f, 1.0f},      {-1.0f, 0.f, -1.0f}};

  std::vector<Vertex3D> expected_lines{
      {1.0f, -2.0f, -1.0f},       {1.0f, -2.0f, 1.0f},
      {1.0f, -2.0f, 1.0f},        {-1.0f, -2.0f, 1.0f},
      {-1.0f, -2.0f, 1.0f},       {-1.0f, -2.0f, -1.0f},
      {-1.0f, -2.0f, -1.0f},      {1.0f, -2.0f, -1.0f},
      {1.0f, -2.0f, -1.0f},       {1.0f, -2.0f, 1.0f},
      {1.0f, -2.0f, 1.0f},        {0.999999, 0.f, 1.000001f},
      {0.999999, 0.f, 1.000001f}, {1.0f, 0.f, -0.999999f},
      {1.0f, 0.f, -0.999999f},    {1.0f, -2.0f, -1.0f},
      {1.0f, 0.f, -0.999999f},    {0.999999, 0.f, 1.000001f},
      {0.999999, 0.f, 1.000001f}, {-1.0f, 0.f, 1.0f},
      {-1.0f, 0.f, 1.0f},         {-1.0f, 0.f, -1.0f},
      {-1.0f, 0.f, -1.0f},        {1.0f, 0.f, -0.999999f},
      {-1.0f, -2.0f, 1.0f},       {-1.0f, -2.0f, -1.0f},
      {-1.0f, -2.0f, -1.0f},      {-1.0f, 0.f, -1.0f},
      {-1.0f, 0.f, -1.0f},        {-1.0f, 0.f, 1.0f},
      {-1.0f, 0.f, 1.0f},         {-1.0f, -2.0f, 1.0f},
      {1.0f, -2.0f, 1.0f},        {-1.0f, -2.0f, 1.0f},
      {-1.0f, -2.0f, 1.0f},       {-1.0f, 0.f, 1.0f},
      {-1.0f, 0.f, 1.0f},         {0.999999, 0.f, 1.000001f},
      {0.999999, 0.f, 1.000001f}, {1.0f, -2.0f, 1.0f},
      {1.0f, -2.0f, -1.0f},       {1.0f, 0.f, -0.999999f},
      {1.0f, 0.f, -0.999999f},    {-1.0f, 0.f, -1.0f},
      {-1.0f, 0.f, -1.0f},        {-1.0f, -2.0f, -1.0f},
      {-1.0f, -2.0f, -1.0f},      {1.0f, -2.0f, -1.0f}};

  std::vector<Vertex3D> expected_triangles{
      expected_vertices[0], expected_vertices[1], expected_vertices[2],
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
  Command command;
  CommandParameters pars = {Move, y, -1.0};
  command.UpdateParameters(pars);
  model.ApplyAphine(command);
  const Vertex3D* expect_v = &expected_vertices.front();
  const Vertex3D* getted_v = &model.GetVertexArray();

  for (std::size_t i = 0; i < model.VertexSize(); ++i) {
    EXPECT_EQ(expect_v[i].x_, getted_v[i].x_);
    EXPECT_EQ(expect_v[i].y_, getted_v[i].y_);
    EXPECT_EQ(expect_v[i].z_, getted_v[i].z_);
  }

  EXPECT_EQ(model.LinesSize(), 48);

  const Vertex3D* expect_l = &expected_lines.front();
  const Vertex3D* getted_l = &model.GetLineArray();

  for (std::size_t i = 0; i < model.LinesSize(); ++i) {
    EXPECT_EQ(expect_l[i].x_, getted_l[i].x_);
    EXPECT_EQ(expect_l[i].y_, getted_l[i].y_);
    EXPECT_EQ(expect_l[i].z_, getted_l[i].z_);
  }

  EXPECT_EQ(model.TrianglesSize(), 36);

  const Vertex3D* expect_t = &expected_triangles.front();
  const Vertex3D* getted_t = &model.GetTriangleArray();

  for (std::size_t i = 0; i < model.TrianglesSize(); ++i) {
    EXPECT_EQ(expect_t[i].x_, getted_t[i].x_);
    EXPECT_EQ(expect_t[i].y_, getted_t[i].y_);
    EXPECT_EQ(expect_t[i].z_, getted_t[i].z_);
  }
}

TEST(move_test_z, t1) {
  s21::Model model;
  const std::string path{"models/cube.obj"};

  std::vector<Vertex3D> expected_vertices{
      {1.0f, -1.0f, -2.0f},     {1.0f, -1.0f, 0.f},
      {-1.0f, -1.0f, 0.f},      {-1.0f, -1.0f, -2.0f},
      {1.0f, 1.0f, -1.999999f}, {0.999999, 1.0f, 0.000001f},
      {-1.0f, 1.0f, 0.f},       {-1.0f, 1.0f, -2.0f}};

  std::vector<Vertex3D> expected_lines{
      {1.0f, -1.0f, -2.0f},        {1.0f, -1.0f, 0.f},
      {1.0f, -1.0f, 0.f},          {-1.0f, -1.0f, 0.f},
      {-1.0f, -1.0f, 0.f},         {-1.0f, -1.0f, -2.0f},
      {-1.0f, -1.0f, -2.0f},       {1.0f, -1.0f, -2.0f},
      {1.0f, -1.0f, -2.0f},        {1.0f, -1.0f, 0.f},
      {1.0f, -1.0f, 0.f},          {0.999999, 1.0f, 0.000001f},
      {0.999999, 1.0f, 0.000001f}, {1.0f, 1.0f, -1.999999f},
      {1.0f, 1.0f, -1.999999f},    {1.0f, -1.0f, -2.0f},
      {1.0f, 1.0f, -1.999999f},    {0.999999, 1.0f, 0.000001f},
      {0.999999, 1.0f, 0.000001f}, {-1.0f, 1.0f, 0.f},
      {-1.0f, 1.0f, 0.f},          {-1.0f, 1.0f, -2.0f},
      {-1.0f, 1.0f, -2.0f},        {1.0f, 1.0f, -1.999999f},
      {-1.0f, -1.0f, 0.f},         {-1.0f, -1.0f, -2.0f},
      {-1.0f, -1.0f, -2.0f},       {-1.0f, 1.0f, -2.0f},
      {-1.0f, 1.0f, -2.0f},        {-1.0f, 1.0f, 0.f},
      {-1.0f, 1.0f, 0.f},          {-1.0f, -1.0f, 0.f},
      {1.0f, -1.0f, 0.f},          {-1.0f, -1.0f, 0.f},
      {-1.0f, -1.0f, 0.f},         {-1.0f, 1.0f, 0.f},
      {-1.0f, 1.0f, 0.f},          {0.999999, 1.0f, 0.000001f},
      {0.999999, 1.0f, 0.000001f}, {1.0f, -1.0f, 0.f},
      {1.0f, -1.0f, -2.0f},        {1.0f, 1.0f, -1.999999f},
      {1.0f, 1.0f, -1.999999f},    {-1.0f, 1.0f, -2.0f},
      {-1.0f, 1.0f, -2.0f},        {-1.0f, -1.0f, -2.0f},
      {-1.0f, -1.0f, -2.0f},       {1.0f, -1.0f, -2.0f}};

  std::vector<Vertex3D> expected_triangles{
      expected_vertices[0], expected_vertices[1], expected_vertices[2],
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
  Command command;
  CommandParameters pars = {Move, z, -1.0};
  command.UpdateParameters(pars);
  model.ApplyAphine(command);
  const Vertex3D* expect_v = &expected_vertices.front();
  const Vertex3D* getted_v = &model.GetVertexArray();

  for (std::size_t i = 0; i < model.VertexSize(); ++i) {
    EXPECT_NEAR(expect_v[i].x_, getted_v[i].x_, 1e-6);
    EXPECT_NEAR(expect_v[i].y_, getted_v[i].y_, 1e-6);
    EXPECT_NEAR(expect_v[i].z_, getted_v[i].z_, 1e-6);
  }

  EXPECT_EQ(model.LinesSize(), 48);

  const Vertex3D* expect_l = &expected_lines.front();
  const Vertex3D* getted_l = &model.GetLineArray();

  for (std::size_t i = 0; i < model.LinesSize(); ++i) {
    EXPECT_NEAR(expect_l[i].x_, getted_l[i].x_, 1e-6);
    EXPECT_NEAR(expect_l[i].y_, getted_l[i].y_, 1e-6);
    EXPECT_NEAR(expect_l[i].z_, getted_l[i].z_, 1e-6);
  }

  EXPECT_EQ(model.TrianglesSize(), 36);

  const Vertex3D* expect_t = &expected_triangles.front();
  const Vertex3D* getted_t = &model.GetTriangleArray();

  for (std::size_t i = 0; i < model.TrianglesSize(); ++i) {
    EXPECT_NEAR(expect_t[i].x_, getted_t[i].x_, 1e-6);
    EXPECT_NEAR(expect_t[i].y_, getted_t[i].y_, 1e-6);
    EXPECT_NEAR(expect_t[i].z_, getted_t[i].z_, 1e-6);
  }
}

TEST(rotate_test_x, t1) {
  s21::Model model;
  const std::string path{"models/cube.obj"};

  std::vector<Vertex3D> expected_vertices{
      {1, 0.155498, 1.40564},    {1, 1.40564, -0.155498},
      {-1, 1.40564, -0.155498},  {-1, 0.155498, 1.40564},
      {1, -1.40564, 0.155497},   {0.999999, -0.155497, -1.40564},
      {-1, -0.155498, -1.40564}, {-1, -1.40564, 0.155498}};

  std::vector<Vertex3D> expected_lines{
      {1, 0.155498, 1.40564},          {1, 1.40564, -0.155498},
      {1, 1.40564, -0.155498},         {-1, 1.40564, -0.155498},
      {-1, 1.40564, -0.155498},        {-1, 0.155498, 1.40564},
      {-1, 0.155498, 1.40564},         {1, 0.155498, 1.40564},
      {1, 0.155498, 1.40564},          {1, 1.40564, -0.155498},
      {1, 1.40564, -0.155498},         {0.999999, -0.155497, -1.40564},
      {0.999999, -0.155497, -1.40564}, {1, -1.40564, 0.155497},
      {1, -1.40564, 0.155497},         {1, 0.155498, 1.40564},
      {1, -1.40564, 0.155497},         {0.999999, -0.155497, -1.40564},
      {0.999999, -0.155497, -1.40564}, {-1, -0.155498, -1.40564},
      {-1, -0.155498, -1.40564},       {-1, -1.40564, 0.155498},
      {-1, -1.40564, 0.155498},        {1, -1.40564, 0.155497},
      {-1, 1.40564, -0.155498},        {-1, 0.155498, 1.40564},
      {-1, 0.155498, 1.40564},         {-1, -1.40564, 0.155498},
      {-1, -1.40564, 0.155498},        {-1, -0.155498, -1.40564},
      {-1, -0.155498, -1.40564},       {-1, 1.40564, -0.155498},
      {1, 1.40564, -0.155498},         {-1, 1.40564, -0.155498},
      {-1, 1.40564, -0.155498},        {-1, -0.155498, -1.40564},
      {-1, -0.155498, -1.40564},       {0.999999, -0.155497, -1.40564},
      {0.999999, -0.155497, -1.40564}, {1, 1.40564, -0.155498},
      {1, 0.155498, 1.40564},          {1, -1.40564, 0.155497},
      {1, -1.40564, 0.155497},         {-1, -1.40564, 0.155498},
      {-1, -1.40564, 0.155498},        {-1, 0.155498, 1.40564},
      {-1, 0.155498, 1.40564},         {1, 0.155498, 1.40564}};

  std::vector<Vertex3D> expected_triangles{
      expected_vertices[0], expected_vertices[1], expected_vertices[2],
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
  Command command;
  CommandParameters pars = {Rotation, x, 10.1};
  command.UpdateParameters(pars);
  model.ApplyAphine(command);
  const Vertex3D* expect_v = &expected_vertices.front();
  const Vertex3D* getted_v = &model.GetVertexArray();
  for (std::size_t i = 0; i < model.VertexSize(); ++i) {
    EXPECT_NEAR(expect_v[i].x_, getted_v[i].x_, 1e-5);
    EXPECT_NEAR(expect_v[i].y_, getted_v[i].y_, 1e-5);
    EXPECT_NEAR(expect_v[i].z_, getted_v[i].z_, 1e-5);
  }

  EXPECT_EQ(model.LinesSize(), 48);
  std::cout << std::endl;
  const Vertex3D* expect_l = &expected_lines.front();
  const Vertex3D* getted_l = &model.GetLineArray();
  for (std::size_t i = 0; i < model.LinesSize(); ++i) {
    EXPECT_NEAR(expect_l[i].x_, getted_l[i].x_, 1e-5);
    EXPECT_NEAR(expect_l[i].y_, getted_l[i].y_, 1e-5);
    EXPECT_NEAR(expect_l[i].z_, getted_l[i].z_, 1e-5);
  }

  EXPECT_EQ(model.TrianglesSize(), 36);

  const Vertex3D* expect_t = &expected_triangles.front();
  const Vertex3D* getted_t = &model.GetTriangleArray();

  for (std::size_t i = 0; i < model.TrianglesSize(); ++i) {
    EXPECT_NEAR(expect_t[i].x_, getted_t[i].x_, 1e-5);
    EXPECT_NEAR(expect_t[i].y_, getted_t[i].y_, 1e-5);
    EXPECT_NEAR(expect_t[i].z_, getted_t[i].z_, 1e-5);
  }
}

TEST(rotate_test_y, t1) {
  s21::Model model;
  const std::string path{"models/cube.obj"};

  std::vector<Vertex3D> expected_vertices{
      {-0.155498, -1, 1.40564}, {-1.40564, -1, -0.155498},
      {0.155498, -1, -1.40564}, {1.40564, -1, 0.155498},
      {-0.155498, 1, 1.40564},  {-1.40564, 1, -0.155499},
      {0.155498, 1, -1.40564},  {1.40564, 1, 0.155498}};

  std::vector<Vertex3D> expected_lines{
      {-0.155498, -1, 1.40564},  {-1.40564, -1, -0.155498},
      {-1.40564, -1, -0.155498}, {0.155498, -1, -1.40564},
      {0.155498, -1, -1.40564},  {1.40564, -1, 0.155498},
      {1.40564, -1, 0.155498},   {-0.155498, -1, 1.40564},
      {-0.155498, -1, 1.40564},  {-1.40564, -1, -0.155498},
      {-1.40564, -1, -0.155498}, {-1.40564, 1, -0.155499},
      {-1.40564, 1, -0.155499},  {-0.155498, 1, 1.40564},
      {-0.155498, 1, 1.40564},   {-0.155498, -1, 1.40564},
      {-0.155498, 1, 1.40564},   {-1.40564, 1, -0.155499},
      {-1.40564, 1, -0.155499},  {0.155498, 1, -1.40564},
      {0.155498, 1, -1.40564},   {1.40564, 1, 0.155498},
      {1.40564, 1, 0.155498},    {-0.155498, 1, 1.40564},
      {0.155498, -1, -1.40564},  {1.40564, -1, 0.155498},
      {1.40564, -1, 0.155498},   {1.40564, 1, 0.155498},
      {1.40564, 1, 0.155498},    {0.155498, 1, -1.40564},
      {0.155498, 1, -1.40564},   {0.155498, -1, -1.40564},
      {-1.40564, -1, -0.155498}, {0.155498, -1, -1.40564},
      {0.155498, -1, -1.40564},  {0.155498, 1, -1.40564},
      {0.155498, 1, -1.40564},   {-1.40564, 1, -0.155499},
      {-1.40564, 1, -0.155499},  {-1.40564, -1, -0.155498},
      {-0.155498, -1, 1.40564},  {-0.155498, 1, 1.40564},
      {-0.155498, 1, 1.40564},   {1.40564, 1, 0.155498},
      {1.40564, 1, 0.155498},    {1.40564, -1, 0.155498},
      {1.40564, -1, 0.155498},   {-0.155498, -1, 1.40564}};

  std::vector<Vertex3D> expected_triangles{
      expected_vertices[0], expected_vertices[1], expected_vertices[2],
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
  Command command;
  CommandParameters pars = {Rotation, y, 10.1};
  command.UpdateParameters(pars);
  model.ApplyAphine(command);
  const Vertex3D* expect_v = &expected_vertices.front();
  const Vertex3D* getted_v = &model.GetVertexArray();
  for (std::size_t i = 0; i < model.VertexSize(); ++i) {
    EXPECT_NEAR(expect_v[i].x_, getted_v[i].x_, 1e-5);
    EXPECT_NEAR(expect_v[i].y_, getted_v[i].y_, 1e-5);
    EXPECT_NEAR(expect_v[i].z_, getted_v[i].z_, 1e-5);
  }

  EXPECT_EQ(model.LinesSize(), 48);
  std::cout << std::endl;
  const Vertex3D* expect_l = &expected_lines.front();
  const Vertex3D* getted_l = &model.GetLineArray();
  for (std::size_t i = 0; i < model.LinesSize(); ++i) {
    EXPECT_NEAR(expect_l[i].x_, getted_l[i].x_, 1e-5);
    EXPECT_NEAR(expect_l[i].y_, getted_l[i].y_, 1e-5);
    EXPECT_NEAR(expect_l[i].z_, getted_l[i].z_, 1e-5);
  }

  EXPECT_EQ(model.TrianglesSize(), 36);

  const Vertex3D* expect_t = &expected_triangles.front();
  const Vertex3D* getted_t = &model.GetTriangleArray();

  for (std::size_t i = 0; i < model.TrianglesSize(); ++i) {
    EXPECT_NEAR(expect_t[i].x_, getted_t[i].x_, 1e-5);
    EXPECT_NEAR(expect_t[i].y_, getted_t[i].y_, 1e-5);
    EXPECT_NEAR(expect_t[i].z_, getted_t[i].z_, 1e-5);
  }
}

TEST(rotate_test_z, t1) {
  s21::Model model;
  const std::string path{"models/cube.obj"};

  std::vector<Vertex3D> expected_vertices{
      {-1.39201, 0.249616, -1},         {-1.39201, 0.249616, 1},
      {0.249616, 1.39201, 1},           {0.249616, 1.39201, -1},
      {-0.249616, -1.39201, -0.999999}, {-0.249615, -1.39201, 1},
      {1.39201, -0.249616, 1},          {1.39201, -0.249616, -1}};

  std::vector<Vertex3D> expected_lines{
      {-1.39201, 0.249616, -1},         {-1.39201, 0.249616, 1},
      {-1.39201, 0.249616, 1},          {0.249616, 1.39201, 1},
      {0.249616, 1.39201, 1},           {0.249616, 1.39201, -1},
      {0.249616, 1.39201, -1},          {-1.39201, 0.249616, -1},
      {-1.39201, 0.249616, -1},         {-1.39201, 0.249616, 1},
      {-1.39201, 0.249616, 1},          {-0.249615, -1.39201, 1},
      {-0.249615, -1.39201, 1},         {-0.249616, -1.39201, -0.999999},
      {-0.249616, -1.39201, -0.999999}, {-1.39201, 0.249616, -1},
      {-0.249616, -1.39201, -0.999999}, {-0.249615, -1.39201, 1},
      {-0.249615, -1.39201, 1},         {1.39201, -0.249616, 1},
      {1.39201, -0.249616, 1},          {1.39201, -0.249616, -1},
      {1.39201, -0.249616, -1},         {-0.249616, -1.39201, -0.999999},
      {0.249616, 1.39201, 1},           {0.249616, 1.39201, -1},
      {0.249616, 1.39201, -1},          {1.39201, -0.249616, -1},
      {1.39201, -0.249616, -1},         {1.39201, -0.249616, 1},
      {1.39201, -0.249616, 1},          {0.249616, 1.39201, 1},
      {-1.39201, 0.249616, 1},          {0.249616, 1.39201, 1},
      {0.249616, 1.39201, 1},           {1.39201, -0.249616, 1},
      {1.39201, -0.249616, 1},          {-0.249615, -1.39201, 1},
      {-0.249615, -1.39201, 1},         {-1.39201, 0.249616, 1},
      {-1.39201, 0.249616, -1},         {-0.249616, -1.39201, -0.999999},
      {-0.249616, -1.39201, -0.999999}, {1.39201, -0.249616, -1},
      {1.39201, -0.249616, -1},         {0.249616, 1.39201, -1},
      {0.249616, 1.39201, -1},          {-1.39201, 0.249616, -1}};

  std::vector<Vertex3D> expected_triangles{
      expected_vertices[0], expected_vertices[1], expected_vertices[2],
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
  Command command;
  CommandParameters pars = {Rotation, z, -15.1};
  command.UpdateParameters(pars);
  model.ApplyAphine(command);
  const Vertex3D* expect_v = &expected_vertices.front();
  const Vertex3D* getted_v = &model.GetVertexArray();
  for (std::size_t i = 0; i < model.VertexSize(); ++i) {
    EXPECT_NEAR(expect_v[i].x_, getted_v[i].x_, 1e-5);
    EXPECT_NEAR(expect_v[i].y_, getted_v[i].y_, 1e-5);
    EXPECT_NEAR(expect_v[i].z_, getted_v[i].z_, 1e-5);
  }

  EXPECT_EQ(model.LinesSize(), 48);
  std::cout << std::endl;
  const Vertex3D* expect_l = &expected_lines.front();
  const Vertex3D* getted_l = &model.GetLineArray();
  for (std::size_t i = 0; i < model.LinesSize(); ++i) {
    EXPECT_NEAR(expect_l[i].x_, getted_l[i].x_, 1e-5);
    EXPECT_NEAR(expect_l[i].y_, getted_l[i].y_, 1e-5);
    EXPECT_NEAR(expect_l[i].z_, getted_l[i].z_, 1e-5);
  }

  EXPECT_EQ(model.TrianglesSize(), 36);

  const Vertex3D* expect_t = &expected_triangles.front();
  const Vertex3D* getted_t = &model.GetTriangleArray();

  for (std::size_t i = 0; i < model.TrianglesSize(); ++i) {
    EXPECT_NEAR(expect_t[i].x_, getted_t[i].x_, 1e-5);
    EXPECT_NEAR(expect_t[i].y_, getted_t[i].y_, 1e-5);
    EXPECT_NEAR(expect_t[i].z_, getted_t[i].z_, 1e-5);
  }
}

TEST(scale_test, t1) {
  s21::Model model;
  const std::string path{"models/cube.obj"};

  std::vector<Vertex3D> expected_vertices{{2.1, -2.1, -2.1}, {2.1, -2.1, 2.1},
                                          {-2.1, -2.1, 2.1}, {-2.1, -2.1, -2.1},
                                          {2.1, 2.1, -2.1},  {2.1, 2.1, 2.1},
                                          {-2.1, 2.1, 2.1},  {-2.1, 2.1, -2.1}};

  std::vector<Vertex3D> expected_lines{
      {2.1, -2.1, -2.1},  {2.1, -2.1, 2.1},   {2.1, -2.1, 2.1},
      {-2.1, -2.1, 2.1},  {-2.1, -2.1, 2.1},  {-2.1, -2.1, -2.1},
      {-2.1, -2.1, -2.1}, {2.1, -2.1, -2.1},  {2.1, -2.1, -2.1},
      {2.1, -2.1, 2.1},   {2.1, -2.1, 2.1},   {2.1, 2.1, 2.1},
      {2.1, 2.1, 2.1},    {2.1, 2.1, -2.1},   {2.1, 2.1, -2.1},
      {2.1, -2.1, -2.1},  {2.1, 2.1, -2.1},   {2.1, 2.1, 2.1},
      {2.1, 2.1, 2.1},    {-2.1, 2.1, 2.1},   {-2.1, 2.1, 2.1},
      {-2.1, 2.1, -2.1},  {-2.1, 2.1, -2.1},  {2.1, 2.1, -2.1},
      {-2.1, -2.1, 2.1},  {-2.1, -2.1, -2.1}, {-2.1, -2.1, -2.1},
      {-2.1, 2.1, -2.1},  {-2.1, 2.1, -2.1},  {-2.1, 2.1, 2.1},
      {-2.1, 2.1, 2.1},   {-2.1, -2.1, 2.1},  {2.1, -2.1, 2.1},
      {-2.1, -2.1, 2.1},  {-2.1, -2.1, 2.1},  {-2.1, 2.1, 2.1},
      {-2.1, 2.1, 2.1},   {2.1, 2.1, 2.1},    {2.1, 2.1, 2.1},
      {2.1, -2.1, 2.1},   {2.1, -2.1, -2.1},  {2.1, 2.1, -2.1},
      {2.1, 2.1, -2.1},   {-2.1, 2.1, -2.1},  {-2.1, 2.1, -2.1},
      {-2.1, -2.1, -2.1}, {-2.1, -2.1, -2.1}, {2.1, -2.1, -2.1}};

  std::vector<Vertex3D> expected_triangles{
      expected_vertices[0], expected_vertices[1], expected_vertices[2],
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
  Command command;
  CommandParameters pars = {Scale, z, 2.1};
  command.UpdateParameters(pars);
  model.ApplyAphine(command);
  const Vertex3D* expect_v = &expected_vertices.front();
  const Vertex3D* getted_v = &model.GetVertexArray();
  for (std::size_t i = 0; i < model.VertexSize(); ++i) {
    EXPECT_NEAR(expect_v[i].x_, getted_v[i].x_, 1e-5);
    EXPECT_NEAR(expect_v[i].y_, getted_v[i].y_, 1e-5);
    EXPECT_NEAR(expect_v[i].z_, getted_v[i].z_, 1e-5);
  }

  EXPECT_EQ(model.LinesSize(), 48);
  std::cout << std::endl;
  const Vertex3D* expect_l = &expected_lines.front();
  const Vertex3D* getted_l = &model.GetLineArray();
  for (std::size_t i = 0; i < model.LinesSize(); ++i) {
    EXPECT_NEAR(expect_l[i].x_, getted_l[i].x_, 1e-5);
    EXPECT_NEAR(expect_l[i].y_, getted_l[i].y_, 1e-5);
    EXPECT_NEAR(expect_l[i].z_, getted_l[i].z_, 1e-5);
  }

  EXPECT_EQ(model.TrianglesSize(), 36);

  const Vertex3D* expect_t = &expected_triangles.front();
  const Vertex3D* getted_t = &model.GetTriangleArray();

  for (std::size_t i = 0; i < model.TrianglesSize(); ++i) {
    EXPECT_NEAR(expect_t[i].x_, getted_t[i].x_, 1e-5);
    EXPECT_NEAR(expect_t[i].y_, getted_t[i].y_, 1e-5);
    EXPECT_NEAR(expect_t[i].z_, getted_t[i].z_, 1e-5);
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}

// another tests analog
