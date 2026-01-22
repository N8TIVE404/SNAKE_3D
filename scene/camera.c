#include "camera.h"
#include <cglm/types.h>
#include <cglm/vec3.h>

Camera initialize_camera(float fov, vec3 location) {
  Camera cam;
  glm_vec3_copy(location, cam.position);
  glm_vec3_copy((vec3){0.0f, 0.0f, -1.0f}, cam.front);
  glm_vec3_copy((vec3){0.0f, 1.0f, 0.0f}, cam.up);
  glm_vec3_copy((vec3){0.0f, 0.0f, 0.0f}, cam.target);
  cam.fov = glm_rad(fov);
  cam.speed = 30.5f;
  cam.yaw = -90.0f;
  cam.pitch = 0.0f;
  cam.deltaTime = 0.0f;

  return cam;
}
