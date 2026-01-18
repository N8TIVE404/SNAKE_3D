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
  vec3 position;
  vec3 front;
  vec3 up;
  vec3 target;
  float fov, speed, yaw, pitch;
} Camera;

Camera initilaize_camera(float, Position *);

#endif
