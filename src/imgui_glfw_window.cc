#include "imgui_glwf_window.h"
#include "model/transform_matrix_builder.h"

#include <iostream>

static void ErrorCallback(const int error, const char *description) {
  std::cerr << "Glfw Error " << error << ": " << description;
}

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action,
    int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

ImguiWindow::ImguiWindow() {

  glfwSetErrorCallback(ErrorCallback);
  if (!glfwInit())
    throw std::runtime_error("Cannot initialize GLFW.");

#if defined(__APPLE__)
  // GL 3.2 + GLSL 150
  const char *glsl_version = "#version 150";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
  // GL 3.0 + GLSL 130
  const char *glsl_version = "#version 130";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  // 3.2+ only
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // 3.0+ only
  /* glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); */
#endif

  window = glfwCreateWindow(1280, 720, "3DViewer_1.0", NULL, NULL);
  if (NULL == window) {
    glfwTerminate();
    throw std::runtime_error("Failed to create GLFW window");
  }

  glfwSetKeyCallback(window, KeyCallback);

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1); // sync rendering loop to the refresh rate of the monitor

  drawer_ = new ModelDrawer();

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);

}

void ImguiWindow::Run() /*const*/ {

  LoadModel("models/lamp.obj");
  Settings s;

  while (!glfwWindowShouldClose(window)) {
    glClearColor(s.clear_color.x, s.clear_color.y, s.clear_color.y,
                                                              s.clear_color.z);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    SetingsWindow(s);

    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    DrawModel(s);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

}

void ImguiWindow::SetingsWindow(Settings& s) {
    ImGui::Begin("Settings");

    if (ImGui::Button("Move")) MoveModel(-0.0f, -0.2f, 0.0f);
    if (ImGui::Button("Rotate")) {
      RotateModel(0.5f, s21::TransformMatrixBuilder::Axis::Z);
      RotateModel(0.5f, s21::TransformMatrixBuilder::Axis::X);
    }
    if (ImGui::Button("Scale")) ScaleModel(0.7f, 0.7f, 0.7f);

    ImGui::ColorEdit3("Back Color", (float *)&s.clear_color);

    ImGui::ColorEdit3("Vertex Color", (float *)&s.vertex_color);
    ImGui::ColorEdit3("Lines Color", (float *)&s.lines_color);
    ImGui::ColorEdit3("Triangles Color", (float *)&s.triangles_color);

    ImGui::End();
}

ImguiWindow::~ImguiWindow() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();
  delete drawer_;
}

int ImguiWindow::LoadModel(const std::string& path) {
  Model model;
  try {
    model.LoadModel(path);
  } catch (const std::exception& e) {
    ErrorCallback(-1, e.what());
    return -1;
  }
  models.push_back(std::move(model));
  return 0; // Dont forget to return some pretty error class
}

static std::vector<_3DVertex> ChooseMethod(const Model& m, GLuint type) {
  if (type == GL_POINTS) return m.GetVertexArray();
  if (type == GL_LINES) return m.GetLineArray();
  return m.GetTriangleArray();
}

int ImguiWindow::DrawModel(Settings& s) {
  drawer_->MakeMVP();

  drawer_->SetColor("MyColor", s.vertex_color);
  drawer_->Draw(ChooseMethod(models.front(), GL_POINTS), GL_POINTS);

  drawer_->SetColor("MyColor", s.lines_color);
  drawer_->Draw(ChooseMethod(models.front(), GL_LINES), GL_LINES);

  /* drawer_->SetColor("MyColor", s.triangles_color); */
  /* drawer_->Draw(ChooseMethod(models.front(), GL_TRIANGLES), GL_TRIANGLES); */
  return 0;
}

int ImguiWindow::MoveModel(float ax, float ay, float az) {
  s21::TransformMatrix m = s21::TransformMatrixBuilder::CreateMoveMatrix(ax, ay, az);
  models.front().TransformModel(m);
  return 0;
}


int ImguiWindow::RotateModel(float angle, int axis) {
  s21::TransformMatrix m = s21::TransformMatrixBuilder::CreateRotationMatrix(angle, axis);
  models.front().TransformModel(m);
  return 0;
}

int ImguiWindow::ScaleModel(float sx, float sy, float sz) {
  s21::TransformMatrix m = s21::TransformMatrixBuilder::CreateScaleMatrix(sx, sy, sz);
  models.front().TransformModel(m);
  return 0;
}
