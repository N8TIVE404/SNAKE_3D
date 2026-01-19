#include "mvp.h"
#include "camera.h"
#include "window.h"
#include <cglm/cam.h>
#include <cglm/mat4.h>
#include <cglm/vec3.h>

void calculate_model(Camera *cam, Position *pos) {
  (void)cam;
  glm_mat4_identity(pos->model);
  glm_translate(pos->model, pos->location);
  glm_rotate(pos->model, glm_rad(pos->angle), pos->axis);
  glm_scale(pos->model, pos->scale);
}

void calculate_view(Camera *cam, Position *pos) {
  glm_mat4_identity(pos->view);
  vec3 temp;
  glm_vec3_add(cam->position, cam->front, temp);
  glm_lookat(cam->position, temp, cam->up, pos->view);
}

void calculate_projection(Camera *cam, Position *pos) {
  glm_mat4_identity(pos->projection);
  glm_perspective(cam->fov, (float)width / height, 1.0f, 100.0f,
                  pos->projection);
}

void calculate_mvp(Camera *cam, Position *pos, mat4 *mvp) {
  calculate_model(cam, pos);
  calculate_view(cam, pos);
  calculate_projection(cam, pos);
  mat4 temp;
  glm_mat4_identity(temp);
  glm_mat4_mul(pos->view, pos->model, temp);
  glm_mat4_mul(pos->projection, temp, (vec4 *)mvp);
}
