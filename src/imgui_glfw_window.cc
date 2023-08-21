#include "imgui_glwf_window.h"

#include "imgui/imgui-knobs.h"

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

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);

}

void ImguiWindow::Run() /*const*/ {

  Settings s;
  /* LoadModel("models/Alien Animal.obj", s); */

  while (!glfwWindowShouldClose(window)) {
    glClearColor(s.clear_color.x, s.clear_color.y, s.clear_color.y,
                                                              s.clear_color.z);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    SetingsWindow(s);
    DrawModel(s);

    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


    glfwSwapBuffers(window);
    glfwPollEvents();
  }

}

static std::string GetFilename(const std::string& full_path) {
  return full_path.substr(full_path.find_last_of('/') + 1);
}

void ImguiWindow::SetingsWindow(Settings& s) {
    ImGui::Begin("Settings");

    if (ImGui::Button("Browse")) s.file_dialog.Open();
    ImGui::SameLine(0.0f, 10.0f);
    ImGui::Text("%s", s.GetFilename().c_str());

    static float value0 = 0, value1 = 0;
    if (ImGuiKnobs::Knob("X Rot", &value0, 0.0f, 360.0f, 1.0f, "X %1.0f", ImGuiKnobVariant_Wiper)) {
      RotateModel((value1 - value0) * 0.0174533f, s21::TransformMatrixBuilder::Axis::X, s.counter);
      value1 = value0;
    }
    ImGui::SameLine();
    static float value2 = 0, value3 = 0;
    if (ImGuiKnobs::Knob("Y Rot", &value2, 0.0f, 360.0f, 1.0f, "Y %1.0f", ImGuiKnobVariant_Wiper)) {
      RotateModel((value3 - value2) * 0.0174533f, s21::TransformMatrixBuilder::Axis::Y, s.counter);
      value3 = value2;
    }
    ImGui::SameLine();
    static float value4 = 0, value5 = 0;
    if (ImGuiKnobs::Knob("Z Rot", &value4, 0.0f, 360.0f, 1.0f, "Y %1.0f", ImGuiKnobVariant_Wiper)) {
      RotateModel((value5 - value4) * 0.0174533f, s21::TransformMatrixBuilder::Axis::Z, s.counter);
      value5 = value4;
    }

    ImGui::SameLine(0.0f, 40.0f);
    static float scale = 100.0f, scale0 = scale;
    if (ImGuiKnobs::Knob("Scale", &scale, 1.0f, 300.0f, 1.0f, "%1.0f %", ImGuiKnobVariant_WiperDot)) {
      scale > scale0 ? ScaleModel(1.0f + (scale - scale0) / scale0, s.counter) :
                       ScaleModel(1.0f - (scale0 - scale) / scale0, s.counter);
      scale0 = scale;
    }

    ImGui::PushButtonRepeat(true);

    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 19.0f);
    if (ImGui::ArrowButton("##up", ImGuiDir_Up) || ImGui::IsKeyPressed(ImGuiKey_UpArrow))
      MoveModel(0.0f, 0.2f, 0.0f, s.counter);
    if (ImGui::ArrowButton("##left", ImGuiDir_Left) || ImGui::IsKeyPressed(ImGuiKey_LeftArrow))
      MoveModel(-0.2f, 0.0f, 0.0f, s.counter);
    ImGui::SameLine(0.0f, 20.0f);
    if (ImGui::ArrowButton("##right", ImGuiDir_Right) || ImGui::IsKeyPressed(ImGuiKey_RightArrow))
      MoveModel(0.2f, 0.0f, 0.0f, s.counter);
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 19.0f);
    if (ImGui::ArrowButton("##down", ImGuiDir_Down) || ImGui::IsKeyPressed(ImGuiKey_DownArrow))
      MoveModel(0.0f, -0.2f, 0.0f, s.counter);
    ImGui::PopButtonRepeat();

    /* Придумать принцип работы слайдера скейлинга, чтобы оно работало адекватно, пока не пойму как. */
    /* Как хочу: крутишь вправо - модель увеличивается в 'x' раз (что делать если разница = 1?) */
    /*           крутишь влево  - модель уменьшается в 'x' раз (что делать если разница = 1?) */
    /* Изначально слайдер в нуле - оригинальный размер модели. */
    /* Если слайдер оказывается в нуле в какой либо момент - размер модели оригинальный. */

    ImGui::ColorEdit3("Back Color", (float *)&s.clear_color);
    ImGui::ColorEdit3("Vertex Color", (float *)&s.vertex_color);
    ImGui::ColorEdit3("Lines Color", (float *)&s.lines_color);
    ImGui::ColorEdit3("Triangles Color", (float *)&s.triangles_color);

    ImGui::SliderInt("Models", &s.counter, 0, models.size() - 1);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
              1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    ImGui::End();

    s.file_dialog.Display();
    if (s.file_dialog.HasSelected()) {
      std::string name = GetFilename(s.file_dialog.GetSelected().string());
      std::string path = std::string("models/") + name;
      if (std::find(s.filenames.begin(), s.filenames.end(), name) == s.filenames.end()) {
        LoadModel(path, s);
        s.filenames.push_back(name);
      }
      s.file_dialog.ClearSelected();
    }
}

ImguiWindow::~ImguiWindow() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();
  delete drawer_;
}

int ImguiWindow::LoadModel(const std::string& path, Settings& s) {
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

int ImguiWindow::DrawModel(const Settings& s) {
  if (models.empty()) return 0;

  drawer_->MakeMVP();

  drawer_->SetColor("MyColor", s.vertex_color);
  drawer_->Draw(ChooseMethod(models[s.counter], GL_POINTS), GL_POINTS);

  drawer_->SetColor("MyColor", s.lines_color);
  drawer_->Draw(ChooseMethod(models[s.counter], GL_LINES), GL_LINES);

  drawer_->SetColor("MyColor", s.triangles_color);
  drawer_->Draw(ChooseMethod(models[s.counter], GL_TRIANGLES), GL_TRIANGLES);
  return 0;
}

int ImguiWindow::MoveModel(float ax, float ay, float az, int position) {
  if (models.empty()) return 0; // SOME BAD SITUATION

  s21::TransformMatrix m = s21::TransformMatrixBuilder::CreateMoveMatrix(ax, ay, az);
  models[position].TransformModel(m);
  return 0;
}


int ImguiWindow::RotateModel(float angle, int axis, int position) {
  if (models.empty()) return 0; // SOME BAD SITUATION

  s21::TransformMatrix m = s21::TransformMatrixBuilder::CreateRotationMatrix(angle, axis);
  models[position].TransformModel(m);
  return 0;
}

int ImguiWindow::ScaleModel(float coef, int position) {
  if (models.empty()) return 0; // SOME BAD SITUATION

  s21::TransformMatrix m = s21::TransformMatrixBuilder::CreateScaleMatrix(coef, coef, coef);
  models[position].TransformModel(m);
  return 0;
}
