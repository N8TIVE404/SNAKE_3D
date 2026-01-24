#include "camera_controller.h"

void camera_controller_update_fps(CameraController *ctl, Camera *cam,
                                  float deltaTime, bool move_forward,
                                  bool move_backward, bool move_left,
                                  bool move_right, float mouse_dx,
                                  float mouse_dy) {
  /* 1. Apply mouse deltas to yaw/pitch */
  /* 2. Clamp pitch */
  /* 3. Recompute basis */
  /* 4. Apply movement using forward/right */
}
