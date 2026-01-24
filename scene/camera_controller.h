#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include "camera.h"

typedef struct CameraController {
  float move_speed;
  float look_sensitivity;

  float pitch_limit; /* radians */
} CameraController;

/* FPS-style controller */
void fps_controller(CameraController *controller, Camera *cam, float deltaTime,
                    bool move_forward, bool move_backward, bool move_left,
                    bool move_right, float mouseDeltaX, float mouseDeltaY);

#endif
