/*
 * Project: PRIMUM ENGINE
 * Author:  KEN KIKAYA
 *
 * This is the functionality for transformations and switching between co-ordinate systems.
 * Unless absolutely necessary, the user is expected to only use the calculate_mvp function, which
 * will in turn call the other functions. The results of each transformation is stored in the Position
 * structure and should be accessed from there instead of making a direct call to the functions. The
 * functions are relatively standard and do not warrant further commenting.
 *
 */
# include "geometry_calculation.h"
# include "models.h"
# include "camera.h"
# include "input.h"

void calculate_model(Position *pos){
    glm_mat4_identity(pos -> model);
    glm_translate(pos -> model, pos -> location);
    glm_rotate(pos -> model, glm_rad(pos -> angle), pos -> axis);
    glm_scale(pos -> model, pos -> scale);
}

void calculate_view(Camera *cam, Position *pos){
    glm_mat4_identity(pos -> view);
    vec3 ans;
    glm_vec3_add(cam -> position, cam -> front, ans);
    glm_lookat(cam -> position, ans, cam -> up, pos -> view);
}

void calculate_projection(Camera *cam, Position *pos){
    glm_mat4_identity(pos -> projection);
    glm_perspective(cam -> fieldOfView, (float)width/height, 0.1f, 1000.0f, pos -> projection);
}

void calculate_mvp(Camera *cam, Position *pos, mat4 mvp){
    calculate_model(pos);
    calculate_view(cam, pos);
    calculate_projection(cam, pos);
    mat4 viewModel;
    glm_mat4_mul(pos -> view, pos -> model, viewModel);
    glm_mat4_mul(pos -> projection, viewModel, mvp);
}
