
#include "camera_system.h"

void camera_update_basis(Camera *cam) {
  vec3 world_up = {0.0f, 1.0f, 0.0f};

  cam->forward[0] = cosf(cam->yaw) * cosf(cam->pitch);
  cam->forward[1] = sinf(cam->pitch);
  cam->forward[2] = sinf(cam->yaw) * cosf(cam->pitch);
  glm_normalize(cam->forward);

  glm_cross(cam->forward, world_up, cam->right);
  glm_normalize(cam->right);

  glm_cross(cam->right, cam->forward, cam->up);
  glm_normalize(cam->up);
}

void camera_update_matrices(Camera *cam) {
  if (!cam->isDirty)
    return;

  camera_update_basis(cam);

  camera_build_projection(cam);
  camera_build_view(cam);

  cam->isDirty = false;
}

void camera_set_position(Camera *cam, vec3 position) {
  glm_vec3_copy(position, cam->position);
  cam->isDirty = true;
}

void camera_set_rotation(Camera *cam, float yaw, float pitch) {
  cam->yaw = yaw;
  cam->pitch = pitch;
  cam->isDirty = true;
}

void camera_build_skybox_view(const Camera *cam, mat4 skyBoxView) {
  glm_mat4_copy((vec4 *)cam->view, skyBoxView);

  // Zero out the translation column (index 3)
  skyBoxView[3][0] = 0.0f;
  skyBoxView[3][1] = 0.0f;
  skyBoxView[3][2] = 0.0f;
}

void camera_build_view(Camera *cam) {
  vec3 target;
  glm_vec3_add(cam->position, cam->forward, target);
  glm_lookat(cam->position, target, cam->up, cam->view);
}

void camera_build_projection(Camera *cam) {
  glm_perspective(cam->fov, cam->aspect, cam->nearZ, cam->farZ,
                  cam->projection);
}
