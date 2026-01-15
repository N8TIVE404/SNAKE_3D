# include "geometry_calculation.h"
# include "camera.h"
# include "models.h"
# include "window.h"

void calculate_mvp(Camera *cam, Position *pos){
    calculate_model(pos);
    calculate_view(cam, pos);
    calculate_projection(cam, pos);
}

void calculate_model(Position *pos){
    glm_mat4_identity(pos->model);
    glm_translate(pos->model, pos->location);
    glm_scale(pos->model, pos->scale);
    glm_rotate(pos->model, glm_rad(30.0f), pos->axis);
}

void calculate_view(Camera *cam, Position *pos){
    vec3 ans;
    glm_vec3_sub(cam->location, cam->front, ans);
    glm_mat4_identity(pos->view);
    glm_lookat(cam->location, ans, cam->up, pos->view);
}

void calculate_projection(Camera *cam, Position *pos){
    glm_mat4_identity(pos->projection);
    glm_perspective(cam->fov, (float)width / height, 0.1f, 1000.0f, pos->projection);
}

