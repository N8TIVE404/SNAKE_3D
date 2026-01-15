# ifndef CAMERA_H
# define CAMERA_H

# include <cglm/cglm.h>

typedef struct Camera{
    vec3 location;
    vec3 up;
    vec3 front;
    vec3 target;
    float fov;
    float deltaTime;
    float speed;
    float yaw;
    float pitch;
} Camera;

Camera initialize_camera(float);

# endif
