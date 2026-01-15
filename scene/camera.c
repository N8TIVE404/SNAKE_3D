# include "camera.h"

Camera initialize_camera(float fov){
    Camera cam;
    cam.fov = glm_rad(fov);
    glm_vec3_copy((vec3){0.0f, 0.0f, 3.0f}, cam.location);
    glm_vec3_copy((vec3){0.0f, 1.0f, 0.0f}, cam.up);
    glm_vec3_copy((vec3){0.0f, 0.0f, -1.0f}, cam.front);
    glm_vec3_copy((vec3){0.0f, 0.0f, 0.0f}, cam.target);
    cam.pitch = 0.0f;
    cam.yaw = -90.0f;

    return cam;
}
