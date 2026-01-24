#include "camera.h"

void initialize_camera(Camera *cam, float fov_rad, float aspect, float near,
                       float far, vec3 position) {
  glm_vec3_copy(position, cam->position);

  cam->yaw = glm_rad(-90.0f);
  cam->pitch = 0.0f;

  cam->fov = fov_rad;
  cam->aspect = aspect;
  cam->nearZ = near;
  cam->farZ = far;

  cam->isDirty = true;
}
