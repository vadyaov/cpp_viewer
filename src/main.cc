#include "imgui_glwf_window.h"

int main() {
  ImguiWindow& glfw_window = ImguiWindow::GetInstance();
  glfw_window.Run();
  return 0;
}
