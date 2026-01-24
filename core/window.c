#include <glad/glad.h>
#include <stdlib.h>
#include <unistd.h>

#include "logger.h"
#include "window.h"

int width = 2160;
int height = 1920;

static void framebuffer_resize(GLFWwindow *window, int w, int h) {
  if (w == 0 || h == 0)
    return;
  width = w;
  height = h;
  glViewport(0, 0, width, height);
}

GLFWwindow *initilaize_window() {
  GLFWwindow *window;

  glfwWindowHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(width, height, "N8TIVE WORLD", NULL, NULL);
  if (!window) {
    FATAL_LOG("Failed to create a window!");
    _exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    FATAL_LOG("Failed to load GLAD");
    _exit(EXIT_FAILURE);
  }

  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);

  glfwSetFramebufferSizeCallback(window, framebuffer_resize);

  return window;
}

void destroy_window(GLFWwindow *window) {
  glfwDestroyWindow(window);
  glfwTerminate();
}
