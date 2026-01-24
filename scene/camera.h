#ifndef CAMERA_H
#define CAMERA_H

#include <cglm/cglm.h>

typedef struct Position {
  vec3 location;
  vec3 scale;
  vec3 axis;
  float angle;
  mat4 model, view, projection;
} Position;

typedef struct Camera {
  vec3 position, forward, right, up;

  float yaw, pitch, fov, aspect, nearZ, farZ;

  mat4 view, projection;

  bool isDirty;
} Camera;

/* Lifecycle */
void initialize_camera(Camera *cam, float fov_rad, float aspect, float near,
                       float far, vec3 position);

#endif
