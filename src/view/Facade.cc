#include "Facade.h"

#include <SDL2/SDL_surface.h>

#include <iostream>

#include "../imgui/imgui-knobs.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
#include "Settings.h"

static void ErrorCallback(const int error, const char *description) {
  std::cerr << "Glfw Error " << error << ": " << description;
}

s21::Facade::Facade() : ctr_{Controller::GetInstance()} {
  glfwSetErrorCallback(ErrorCallback);
  if (!glfwInit()) throw std::runtime_error("Cannot initialize GLFW.");

#if defined(__APPLE__)
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

  const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
  window =
      glfwCreateWindow(mode->width, mode->height, "3DViewer_2.0", NULL, NULL);
  if (NULL == window) {
    glfwTerminate();
    throw std::runtime_error("Failed to create GLFW window");
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(
      1);  // sync rendering loop to the refresh rate of the monitor

  drawer_ = ModelDrawer::GetInstance();

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;

  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);
}

void s21::Facade::Run() const {
  Settings s = Settings::Builder().Build();
  LoadModel(std::string(s.filenames.at(0)));

  while (!glfwWindowShouldClose(window)) {
    glClearColor(s.clear_color.x, s.clear_color.y, s.clear_color.z,
                 s.clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    DrawModel(s);
    SetingsWindow(s);

    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  s.Save();
}

void s21::Facade::SetingsWindow(Settings &s) const {
  ImGui::Begin("Settings");

  if (ImGui::Button("Browse")) s.file_dialog.Open();
  ImGui::SameLine(0.0f, 10.0f);
  std::string path = s.GetFilename().c_str();
  std::string filename = path.substr(path.find_last_of('/') + 1);
  ImGui::Text("%s", filename.c_str());

  if (!ctr_->Empty()) {
    ImGui::Text("%zu vertices; ", ctr_->VertexNum(s.counter));
    ImGui::SameLine();
    ImGui::Text("%zu elements", ctr_->SurfaceNum(s.counter));
  }

  ImGui::SliderInt("Models", &s.counter, 0, ctr_->HowMany() - 1);

  if (ImGui::CollapsingHeader("Rotation & Scale")) {
    static float value0 = 0, value1 = 0;
    if (ImGuiKnobs::Knob("X Rot", &value0, 0.0f, 360.0f, 1.0f, "X %1.0f",
                         ImGuiKnobVariant_Wiper)) {
      CommandParameters pars = {Rotation, x, (value1 - value0) * 0.0174533f};
      ctr_->UpdateCommand(pars);
      ctr_->SendCommand(s.counter);
      value1 = value0;
    }
    ImGui::SameLine();
    static float value2 = 0, value3 = 0;
    if (ImGuiKnobs::Knob("Y Rot", &value2, 0.0f, 360.0f, 1.0f, "Y %1.0f",
                         ImGuiKnobVariant_Wiper)) {
      CommandParameters pars = {Rotation, y, (value3 - value2) * 0.0174533f};
      ctr_->UpdateCommand(pars);
      ctr_->SendCommand(s.counter);
      value3 = value2;
    }
    ImGui::SameLine();
    static float value4 = 0, value5 = 0;
    if (ImGuiKnobs::Knob("Z Rot", &value4, 0.0f, 360.0f, 1.0f, "Y %1.0f",
                         ImGuiKnobVariant_Wiper)) {
      CommandParameters pars = {Rotation, z, (value5 - value4) * 0.0174533f};
      ctr_->UpdateCommand(pars);
      ctr_->SendCommand(s.counter);
      value5 = value4;
    }

    ImGui::SameLine(0.0f, 40.0f);
    static float scale = 100.0f, scale0 = scale;
    if (ImGuiKnobs::Knob("Scale", &scale, 1.0f, 300.0f, 1.0f, "%1.0f %",
                         ImGuiKnobVariant_WiperDot)) {
      double value = scale > scale0 ? 1.0f + (scale - scale0) / scale0
                                    : 1.0f - (scale0 - scale) / scale0;
      CommandParameters pars = {Scale, x, value};
      ctr_->UpdateCommand(pars);
      ctr_->SendCommand(s.counter);
      scale0 = scale;
    }
  }

  if (ImGui::CollapsingHeader("Movement & Primitives")) {
    ImGui::SliderFloat("Move Speed", &s.move_speed, 0.1f, 5.0f);

    ImGui::PushButtonRepeat(true);

    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 19.0f);
    if (ImGui::ArrowButton("##up", ImGuiDir_Up) ||
        ImGui::IsKeyPressed(ImGuiKey_UpArrow) ||
        ImGui::IsKeyPressed(ImGuiKey_W)) {
      CommandParameters pars = {Move, y, s.move_speed};
      ctr_->UpdateCommand(pars);
      ctr_->SendCommand(s.counter);
    }
    ImGui::SameLine(0.0f, 50.0f);
    ImGui::Checkbox("GL_POINTS", &s.points);
    ImGui::SameLine();

    if (ImGui::Checkbox("Round Points", &s.rounded)) {
      if (s.rounded == true) {
        glEnable(GL_POINT_SMOOTH);
      } else {
        glDisable(GL_POINT_SMOOTH);
      }
    }

    if (ImGui::ArrowButton("##left", ImGuiDir_Left) ||
        ImGui::IsKeyPressed(ImGuiKey_LeftArrow) ||
        ImGui::IsKeyPressed(ImGuiKey_A)) {
      CommandParameters pars = {Move, x, -s.move_speed};
      ctr_->UpdateCommand(pars);
      ctr_->SendCommand(s.counter);
    }
    ImGui::SameLine(0.0f, 20.0f);
    if (ImGui::ArrowButton("##right", ImGuiDir_Right) ||
        ImGui::IsKeyPressed(ImGuiKey_RightArrow) ||
        ImGui::IsKeyPressed(ImGuiKey_D)) {
      CommandParameters pars = {Move, x, s.move_speed};
      ctr_->UpdateCommand(pars);
      ctr_->SendCommand(s.counter);
    }

    ImGui::SameLine(0.0f, 30.0f);
    ImGui::Checkbox("GL_LINES", &s.lines);
    ImGui::SameLine(0.0f, 15.0f);
    if (ImGui::Checkbox("Strippled line", &s.strippled)) {
      if (s.strippled == true) {
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, 0x0FF0);
      } else
        glDisable(GL_LINE_STIPPLE);
    }
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 19.0f);
    if (ImGui::ArrowButton("##down", ImGuiDir_Down) ||
        ImGui::IsKeyPressed(ImGuiKey_DownArrow) ||
        ImGui::IsKeyPressed(ImGuiKey_S)) {
      CommandParameters pars = {Move, y, -s.move_speed};
      ctr_->UpdateCommand(pars);
      ctr_->SendCommand(s.counter);
    }

    ImGui::SameLine(0.0f, 50.0f);
    ImGui::Checkbox("GL_TRIANGLES", &s.triangles);

    if (ImGui::Button("MoveBack") || ImGui::IsKeyPressed(ImGuiKey_Q)) {
      CommandParameters pars = {Move, z, -s.move_speed};
      ctr_->UpdateCommand(pars);
      ctr_->SendCommand(s.counter);
    }
    ImGui::SameLine();
    if (ImGui::Button("MoveForward") || ImGui::IsKeyPressed(ImGuiKey_E)) {
      CommandParameters pars = {Move, z, s.move_speed};
      ctr_->UpdateCommand(pars);
      ctr_->SendCommand(s.counter);
    }

    ImGui::PopButtonRepeat();
  }

  if (ImGui::CollapsingHeader("Colors")) {
    ImGui::ColorEdit3("Back Color", (float *)&s.clear_color);
    ImGui::ColorEdit3("Vertex Color", (float *)&s.vertex_color);
    ImGui::ColorEdit3("Lines Color", (float *)&s.lines_color);
    ImGui::ColorEdit3("Triangles Color", (float *)&s.triangles_color);
  }

  ImGui::SliderFloat("Point Size", &s.point_size, 0, 15.0f);

  ImGui::SliderInt("Line Width", &s.line_width, 0, 10);

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
    std::string path = s.file_dialog.GetSelected().string();
    std::string filename = path.substr(path.find_last_of('/') + 1);
    if (std::find(s.filenames.begin(), s.filenames.end(), filename) ==
        s.filenames.end()) {
      LoadModel(path);
      s.filenames.push_back(path);
    }
    s.file_dialog.ClearSelected();
  }
}

void s21::Facade::MakeScreenShot(bool bmp, bool jpg) const {
  int height = 0;
  int width = 0;
  glfwGetFramebufferSize(window, &width, &height);

  SDL_Surface *temp = SDL_CreateRGBSurface(
      SDL_SWSURFACE, width, height, 24, 0x000000FF, 0x0000FF00, 0x00FF0000, 0);
  if (temp == NULL) ErrorCallback(1, "SDL_Surface creation failed.");

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

s21::Facade::~Facade() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();
  delete drawer_;
  delete ctr_;
}

void s21::Facade::LoadModel(const std::string &path) const {
  try {
    ctr_->AddModel(path);
  } catch (const std::exception &e) {
    ErrorCallback(2, e.what());
    throw;
  }
}

void s21::Facade::DrawModel(const Settings &s) const {
  if (ctr_->Empty()) return;

  drawer_->MakeMVP(s.ortho);

  if (s.points) {
    drawer_->SetSize("PointSize", s.point_size);
    drawer_->SetColor("MyColor", s.vertex_color);
    drawer_->Draw(ctr_->GetVertexSize(s.counter), &ctr_->GetVertices(s.counter),
                  GL_POINTS);
  }

  if (s.lines) {
    drawer_->SetColor("MyColor", s.lines_color);
    glLineWidth(s.line_width);
    drawer_->Draw(ctr_->GetLinesSize(s.counter), &ctr_->GetLines(s.counter),
                  GL_LINES);
  }

  if (s.triangles) {
    drawer_->SetColor("MyColor", s.triangles_color);
    drawer_->Draw(ctr_->GetTrianglesSize(s.counter),
                  &ctr_->GetTriangles(s.counter), GL_TRIANGLES);
  }
}
