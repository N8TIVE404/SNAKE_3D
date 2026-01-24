#ifndef CAMERA_SYSTEM_H
#define CAMERA_SYSTEM_H

#include "camera.h"

/* Regular view */
void camera_build_view(Camera *cam);

/* Skybox view (translation removed) */
void camera_build_skybox_view(const Camera *cam, mat4 out_view);

/* Projection */
void camera_build_projection(Camera *cam);

/* Pose */
void camera_set_position(Camera *cam, vec3 position);
void camera_set_rotation(Camera *cam, float yaw, float pitch);

/* Update */
void camera_update_basis(Camera *cam);
void camera_update_matrices(Camera *cam);

#endif
