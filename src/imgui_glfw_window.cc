#include "imgui_glwf_window.h"

#include "imgui/imgui-knobs.h"

#include "model/transform_matrix_builder.h"

#include <iostream>
#include <SDL2/SDL_surface.h>

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
    glClearColor(s.clear_color.x, s.clear_color.y, s.clear_color.z,
                                                              s.clear_color.w);
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

    ImGui::SliderInt("Models", &s.counter, 0, models.size() - 1); // bag when 0 models loaded

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

    ImGui::SliderFloat("Move Speed", &s.move_speed, 0.1f, 5.0f);

    ImGui::PushButtonRepeat(true);

    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 19.0f);
    if (ImGui::ArrowButton("##up", ImGuiDir_Up) ||
        ImGui::IsKeyPressed(ImGuiKey_UpArrow) || ImGui::IsKeyPressed(ImGuiKey_W))
      MoveModel(0.0f, s.move_speed, 0.0f, s.counter);
    ImGui::SameLine(0.0f, 50.0f);
    ImGui::Checkbox("GL_POINTS", &s.points);
    ImGui::SameLine();

    if (ImGui::Checkbox("Round Points", &s.rounded)) {
      if (s.rounded == true) {
          glEnable(GL_POINT_SMOOTH);
          glEnable(GL_BLEND);
          glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      } else {
          glDisable(GL_POINT_SMOOTH);
          glDisable(GL_BLEND);
      }
    }

    if (ImGui::ArrowButton("##left", ImGuiDir_Left) ||
        ImGui::IsKeyPressed(ImGuiKey_LeftArrow) || ImGui::IsKeyPressed(ImGuiKey_A))
      MoveModel(-s.move_speed, 0.0f, 0.0f, s.counter);
    ImGui::SameLine(0.0f, 20.0f);
    if (ImGui::ArrowButton("##right", ImGuiDir_Right) ||
        ImGui::IsKeyPressed(ImGuiKey_RightArrow) || ImGui::IsKeyPressed(ImGuiKey_D))
      MoveModel(s.move_speed, 0.0f, 0.0f, s.counter);

    ImGui::SameLine(0.0f, 30.0f);
    ImGui::Checkbox("GL_LINES", &s.lines);
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 19.0f);
    if (ImGui::ArrowButton("##down", ImGuiDir_Down)
        || ImGui::IsKeyPressed(ImGuiKey_DownArrow) || ImGui::IsKeyPressed(ImGuiKey_S))
      MoveModel(0.0f, -s.move_speed, 0.0f, s.counter);

    ImGui::SameLine(0.0f, 50.0f);
    ImGui::Checkbox("GL_TRIANGLES", &s.triangles);

    ImGui::PopButtonRepeat();

    ImGui::ColorEdit3("Back Color", (float *)&s.clear_color);
    ImGui::ColorEdit3("Vertex Color", (float *)&s.vertex_color);
    ImGui::ColorEdit3("Lines Color", (float *)&s.lines_color);
    ImGui::ColorEdit3("Triangles Color", (float *)&s.triangles_color);

    ImGui::SliderFloat("Point Size", &s.point_size, 0, 15.0f);

    if (ImGui::SliderFloat("Line Width", &s.line_width, 0, 10.0f)) {
      glLineWidth(s.line_width);
    }


    ImGui::Checkbox("ORTHOGRAPHIC PROJECTION", &s.ortho);

    if (ImGui::Button("ScreenShot")) MakeScreenShot(s.bmp, s.jpg);
    ImGui::SameLine();
    ImGui::Checkbox("BMP", &s.bmp);
    ImGui::SameLine();
    ImGui::Checkbox("JPG", &s.jpg);

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

void ImguiWindow::MakeScreenShot(bool bmp, bool jpg) {
  int height = 0;
  int width = 0;
  glfwGetFramebufferSize(window, &width, &height);

  std::cout << "height = " << height << "\nwidth = " << width << std::endl;

  SDL_Surface *temp = SDL_CreateRGBSurface(
      SDL_SWSURFACE, width, height, 24, 0x000000FF, 0x0000FF00, 0x00FF0000, 0);
  if (temp == NULL) ErrorCallback(1, "CreateRGBSurface failed");

  char *pixels = static_cast<char *>(calloc(width * height * 3, 1));
  if (pixels) {
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    for (int i = 0; i < height; i++)
      std::memcpy((static_cast<char *>(temp->pixels)) + temp->pitch * i,
                  pixels + 3 * width * (height - i - 1), width * 3);
    if (bmp) SDL_SaveBMP(temp, "ScreenShot.bmp");
    if (jpg) SDL_SaveBMP(temp, "ScreenShot.jpeg");
    SDL_FreeSurface(temp);
    free(pixels);
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

int ImguiWindow::DrawModel(const Settings& s) {
  if (models.empty()) return 0;

  drawer_->MakeMVP(s.ortho);

  if (s.points) {

    drawer_->SetSize("PointSize", s.point_size);
    drawer_->SetColor("MyColor", s.vertex_color);
    drawer_->Draw(models[s.counter].GetVertexArray(), GL_POINTS);
  }

  if (s.lines) {
    drawer_->SetColor("MyColor", s.lines_color);
    drawer_->Draw(models[s.counter].GetLineArray(), GL_LINES);
  }

  if (s.triangles) {
    drawer_->SetColor("MyColor", s.triangles_color);
    drawer_->Draw(models[s.counter].GetTriangleArray(), GL_TRIANGLES);
  }

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
