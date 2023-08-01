#include <GLFW/glfw3.h>

#include <iostream>

void ErrorCallback(int error, const char* description) {
  std::cerr << "Glfw Error " << error << ':' << description << std::endl;
}

static void KeyCallback(GLFWwindow* window, int key, int scancode,
    int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main() {
  GLFWwindow *window;

  glfwSetErrorCallback(ErrorCallback);

  /* Initialize the library */

  if (!glfwInit())
    return -1;

#if defined(__APPLE__)
  // GL 3.2 + GLSL 150
  /* const char *glsl_version = "#version 150"; */
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
  // GL 3.0 + GLSL 130
  /* const char *glsl_version = "#version 130"; */
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  // 3.2+ only
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // 3.0+ only
  /* glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); */
#endif

  /* Create a windowed mode window and its OpenGL context */

  window = glfwCreateWindow(640, 480, "viewer", NULL, NULL);

  if (!window) {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */

  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, KeyCallback);

  /* Loop until the user closes the window */

  while (!glfwWindowShouldClose(window)) {

    /* Render here */

    glClear(GL_COLOR_BUFFER_BIT);

    /* Swap front and back buffers */

    glfwSwapBuffers(window);

    /* Poll for and process events */

    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
