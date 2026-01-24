#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <stdbool.h>

#include "camera.h"
#include "input.h"

void process_kbinput(GLFWwindow *window) {
  Camera *cam = glfwGetWindowUserPointer(window);

  float velocity = cam->speed * cam->deltaTime;
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    glm_vec3_muladds(cam->front, velocity, cam->position);
  }

  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    glm_vec3_mulsubs(cam->front, velocity, cam->position);
  }

  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    vec3 temp;
    glm_cross(cam->up, cam->front, temp);
    glm_normalize(temp);
    glm_vec3_muladds(temp, velocity, cam->position);
  }

  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    vec3 temp;
    glm_cross(cam->front, cam->up, temp);
    glm_normalize(temp);
    glm_vec3_muladds(temp, velocity, cam->position);
  }
}

static double lastX = 0.0f;
static double lastY = 0.0f;
static bool firstTime = true;
static void cursor_callback(GLFWwindow *window, double posX, double posY) {
  Camera *cam = glfwGetWindowUserPointer(window);

  if (firstTime) {
    lastX = posX;
    lastY = posY;
    firstTime = false;
    return;
  }

  float offsetX = posX - lastX;
  lastX = posX;

  float offsetY = lastY - posY;
  lastY = posY;

  offsetX *= 0.1f;
  offsetY *= 0.1f;

  cam->pitch += offsetY;
  cam->yaw += offsetX;

  if (cam->pitch > 89.0f)
    cam->pitch = 89.0f;
  if (cam->pitch < -89.0f)
    cam->pitch = -89.0f;

  vec3 direction;
  direction[0] = cos(glm_rad(cam->yaw)) * cos(glm_rad(cam->pitch));
  direction[1] = sin(glm_rad(cam->pitch));
  direction[2] = sin(glm_rad(cam->yaw)) * cos(glm_rad(cam->pitch));
  glm_normalize(direction);
  glm_vec3_copy(direction, cam->front);
}

static void scroll_callback(GLFWwindow *window, double offsetX,
                            double offsetY) {
  Camera *cam = glfwGetWindowUserPointer(window);

  cam->fov -= offsetY;
  if (cam->fov > 60.0f)
    cam->fov = 60.0f;
  if (cam->fov < 1.0f)
    cam->fov = 1.0f;

  cam->position[0] += (float)offsetX;
}

void initialize_mouse_callback(GLFWwindow *window) {
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetCursorPosCallback(window, cursor_callback);
  glfwSetScrollCallback(window, scroll_callback);
}
