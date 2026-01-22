#include <cglm/vec3.h>
#include <glad/glad.h>

#include "camera.h"
#include "input.h"
#include "logger.h"
#include "mesh.h"
#include "mvp.h"
#include "primitives.h"
#include "render.h"
#include "shaders.h"
#include "terrain.h"
#include "textures.h"
#include "window.h"

int main(void) {
  GLFWwindow *window = initilaize_window();

  GLuint shader =
      create_program("../assets/shaders", "shader.vert", "shader.frag");
  INFO_LOG("Created a shader program with ID %d.", shader);

  GLuint boxShader =
      create_program("../assets/shaders", "skybox.vert", "skybox.frag");
  INFO_LOG("Created a shader program with ID %d.", boxShader);

  float lastTime = 0.0f;
  Camera cam = initialize_camera(45.0f, (vec3){8000.0f, 1200.0f, 5000.0f});
  glfwSetWindowUserPointer(window, &cam);

  Terrain terrain = load_terrain();
  Position base = {.scale = {13.5f, 13.5f, 13.5f},
                   .angle = 0.0f,
                   .location = {0.0f, 0.0f, -8000.0f},
                   .axis = {1.0f, 0.0f, 1.0f}};
  glm_mat4_identity(base.projection);
  glm_mat4_identity(base.model);
  glm_mat4_identity(base.view);

  glUseProgram(terrain.shader);
  GLuint terrainMvp = glGetUniformLocation(terrain.shader, "mvp");

  Mesh cube = setup_cube();
  Position pos;
  glm_vec3_copy((vec3){0.0f, 0.0f, 0.0f}, pos.location);
  glm_vec3_copy((vec3){0.0f, 1.0f, 0.0f}, pos.axis);
  glm_vec3_copy((vec3){0.5f, 0.5f, 0.5f}, pos.scale);
  pos.angle = 20.0f;

  Mesh sphere = setup_sphere();
  Position pos2;
  glm_vec3_copy((vec3){1.0f, 1.0f, 0.0f}, pos2.location);
  glm_vec3_copy((vec3){0.0f, 1.0f, 0.0f}, pos2.axis);
  glm_vec3_copy((vec3){0.5f, 0.5f, 0.5f}, pos2.scale);
  pos2.angle = 20.0f;

  Skybox box = setup_skybox(boxShader);
  Position boxPos;
  glm_vec3_copy((vec3){0.0f, 0.0f, 0.0f}, boxPos.location);
  glm_vec3_copy((vec3){0.0f, 1.0f, 0.0f}, boxPos.axis);
  glm_vec3_copy((vec3){0.1f, 0.1f, 0.1f}, boxPos.scale);
  glm_mat4_identity(boxPos.view);
  glm_mat4_identity(boxPos.projection);

  glUseProgram(shader);
  GLuint uniformMvp = glGetUniformLocation(shader, "mvp");
  GLuint uniformTex = glGetUniformLocation(shader, "tex");
  glUniform1i(uniformTex, 0);

  glUseProgram(boxShader);
  GLuint uniformCubeSampler = glGetUniformLocation(boxShader, "cubeSampler");
  GLuint uniformView = glGetUniformLocation(boxShader, "view");
  GLuint uniformProjection = glGetUniformLocation(boxShader, "projection");

  glUniform1i(uniformCubeSampler, 10);

  glEnable(GL_DEPTH_TEST);

  while (!glfwWindowShouldClose(window)) {
    float current = glfwGetTime();
    cam.deltaTime = current - lastTime;
    lastTime = current;

    glClearColor(0.6f, 0.2f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    draw_skybox(&box, &cam, &boxPos, boxShader, uniformView, uniformProjection);

    draw_mesh(&cube, &cam, &pos2, shader, uniformMvp);
    pos2.angle += 1.0f;

    draw_mesh(&sphere, &cam, &pos, shader, uniformMvp);
    pos.angle += 1.0f;

    render_terrain(&terrain, &cam, &base, terrainMvp);

    process_kbinput(window);
    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  INFO_LOG("Destroying window and terminating GLFW...");
  destroy_window(window);
  free(sphere.vertices);
  free(sphere.indices);
  free(terrain.vertices);
  free(terrain.indices);

  return 0;
}
